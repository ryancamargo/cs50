from flask import Flask, render_template, request, redirect, session, flash, send_file
import sqlite3
from datetime import datetime, timedelta
import os
from cryptography.fernet import Fernet

app = Flask(__name__)
app.secret_key = os.urandom(24)

# Generate a secret key for encryption
key = Fernet.generate_key()

# Function to encrypt password
def encrypt_password(password):
    cipher_suite = Fernet(key)
    encrypted_password = cipher_suite.encrypt(password.encode('utf-8'))
    return encrypted_password.decode('utf-8')

# Function to decrypt password
def decrypt_password(encrypted_password):
    cipher_suite = Fernet(key)
    decrypted_password = cipher_suite.decrypt(encrypted_password.encode('utf-8'))
    return decrypted_password.decode('utf-8')

# Function to check password expiry and send notifications
def check_password_expiry():
    conn = sqlite3.connect('manager.db')
    c = conn.cursor()
    c.execute('SELECT id, user_id, name, password, last_updated FROM credentials')
    credentials = c.fetchall()
    conn.close()

    for credential in credentials:
        credential_id, user_id, name, password, last_updated = credential
        expiry_date = last_updated + timedelta(days=90)  # Password expiry period (90 days)
        if datetime.now() > expiry_date:
            # Notify user about password expiry
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('SELECT email FROM users WHERE id = ?', (user_id,))
            user_email = c.fetchone()[0]
            conn.close()
            send_password_expiry_notification(user_email, name)

@app.route('/')
def home():
    if 'user_id' in session:
        user_id = session['user_id']
        conn = sqlite3.connect('manager.db')
        c = conn.cursor()
        c.execute('SELECT * FROM credentials WHERE user_id = ?', (user_id,))
        credentials = c.fetchall()
        conn.close()
        return render_template('home.html', credentials=credentials)
    return redirect('/login')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        email = request.form.get('email')
        password = request.form.get('password')
        if username and email and password:
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('INSERT INTO users (username, email, password_hash) VALUES (?, ?, ?)', (username, email, encrypt_password(password)))
            conn.commit()
            conn.close()
            flash('Registration successful. Please log in.', 'success')
            return redirect('/login')  # Redirect to login page after registration
        else:
            flash('All fields are required.', 'error')
    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        if email and password:
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('SELECT * FROM users WHERE email = ? AND password_hash = ?', (email, encrypt_password(password)))
            user = c.fetchone()
            conn.close()
            if user:
                session['user_id'] = user[0]
                flash('Login successful', 'success')
                return redirect('/')  # Redirect to home page after successful login
            else:
                flash('Invalid email or password', 'error')
        else:
            flash('Email and password are required', 'error')
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    flash('Logged out successfully.', 'success')
    return redirect('/login')

@app.route('/home')
def house():
    if 'user_id' in session:
        user_id = session['user_id']
        conn = sqlite3.connect('manager.db')
        c = conn.cursor()
        c.execute('SELECT * FROM credentials WHERE user_id = ?', (user_id,))
        credentials = c.fetchall()
        conn.close()
        return render_template('home.html', credentials=credentials)
    return redirect('/login')

@app.route('/add_credential', methods=['POST'])
def add_credential():
    if 'user_id' in session:
        user_id = session['user_id']
        name = request.form.get('name')
        username = request.form.get('username')
        password = request.form.get('password')
        if name and username and password:
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('INSERT INTO credentials (user_id, name, username, password) VALUES (?, ?, ?, ?)', (user_id, name, username, password))
            conn.commit()
            conn.close()
            flash('Credential added successfully.', 'success')
        else:
            flash('All fields are required.', 'error')
    return redirect('/home')

@app.route('/edit_credential/<int:credential_id>', methods=['GET', 'POST'])
def edit_credential(credential_id):
    if 'user_id' in session:
        user_id = session['user_id']
        if request.method == 'POST':
            name = request.form.get('name')
            username = request.form.get('username')
            password = request.form.get('password')
            if name and username and password:
                conn = sqlite3.connect('manager.db')
                c = conn.cursor()
                c.execute('UPDATE credentials SET name = ?, username = ?, password = ? WHERE id = ? AND user_id = ?', (name, username, password, credential_id, user_id))
                conn.commit()
                conn.close()
                flash('Credential updated successfully.', 'success')
            else:
                flash('All fields are required.', 'error')
        else:
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('SELECT * FROM credentials WHERE id = ? AND user_id = ?', (credential_id, user_id))
            credential = c.fetchone()
            conn.close()
            if credential:
                return render_template('edit.html', credential=credential)
            else:
                flash('Credential not found.', 'error')
    return redirect('/home')

@app.route('/delete_credential/<int:credential_id>')
def delete_credential(credential_id):
    if 'user_id' in session:
        user_id = session['user_id']
        conn = sqlite3.connect('manager.db')
        c = conn.cursor()
        c.execute('DELETE FROM credentials WHERE id = ? AND user_id = ?', (credential_id, user_id))
        conn.commit()
        conn.close()
        flash('Credential deleted successfully.', 'success')
    return redirect('/home')

@app.route('/profile')
def profile():
    if 'user_id' in session:
        user_id = session['user_id']
        conn = sqlite3.connect('manager.db')
        c = conn.cursor()
        c.execute('SELECT * FROM users WHERE id = ?', (user_id,))
        user = c.fetchone()
        conn.close()
        if user:
            return render_template('profile.html', user=user)
    return redirect('/login')

@app.route('/update_profile', methods=['POST'])
def update_profile():
    if 'user_id' in session:
        user_id = session['user_id']
        email = request.form.get('email')
        password = request.form.get('password')
        if email and password:
            # Update email and/or password in the database
            conn = sqlite3.connect('manager.db')
            c = conn.cursor()
            c.execute('UPDATE users SET email = ?, password_hash = ? WHERE id = ?', (email, encrypt_password(password), user_id))
            conn.commit()
            conn.close()
            flash('Profile updated successfully', 'success')
        else:
            flash('Email and password are required', 'error')
    return redirect('/profile')

@app.route('/backup')
def backup():
    if 'user_id' in session:
        user_id = session['user_id']
        conn = sqlite3.connect('manager.db')
        c = conn.cursor()
        c.execute('SELECT * FROM credentials WHERE user_id = ?', (user_id,))
        credentials = c.fetchall()
        conn.close()

        # Generate backup file
        backup_data = '\n'.join([f'{credential[2]}:{credential[3]}:{credential[4]}' for credential in credentials])
        with open(f'user_{user_id}_backup.txt', 'w') as f:
            f.write(backup_data)

        # Send backup file to user
        return send_file(f'user_{user_id}_backup.txt', as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)
