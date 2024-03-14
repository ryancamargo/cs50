import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies) and ensure templates to autoreload
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Is API key set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")   # Remember --> export API_KEY=value


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get stocks and shares that the user has
    stocks = db.execute('SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0', user_id=session['user_id'])

    # Get users cash balance
    cash = db.execute('SELECT cash FROM users WHERE id = :user_id', user_id=session['user_id'])[0]['cash']

    # Initialize variables for total values
    total_value = cash
    grand_total = cash

    # Iterate over stocks and add price and total value
    for stock in stocks:
        quote = lookup(stock['symbol'])
        #stock["name"] = quote["name"]
        stock['price'] = quote['price']
        stock['value'] = stock['price'] * stock['total_shares']
        total_value += stock['value']
        grand_total += stock['value']

    return render_template('index.html', stocks=stocks, cash=cash, total_value=total_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        symbol = request.form.get('symbol').upper()
        shares = request.form.get('shares')
        if not symbol:
            return apology('Must provide symbol')
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology('Must provide a positive integer as number of shares')

        quote = lookup(symbol)
        if quote is None:
            return apology('Stock symbol not found')

        price = quote['price']
        total_cost = int(shares) * price
        cash = db.execute('SELECT cash FROM users WHERE id = :user_id', user_id=session['user_id'])[0]['cash']

        if cash < total_cost:
            return apology('No suficient funds')

        # Update users table
        db.execute('UPDATE users SET cash = cash - :total_cost WHERE id = :user_id', total_cost=total_cost, user_id=session['user_id'])

        # Add purchase to history table
        db.execute('INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)', user_id=session['user_id'], symbol=symbol, shares=shares, price=price)

        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}")
        return redirect('/')

    else:
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute('SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC', user_id=session['user_id'])

    return render_template('history.html', transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        quote = lookup(symbol)
        if not quote:
            return apology('Invalid stock symbol', 400)
        return render_template('quote.html', quote=quote)
    else:
        return render_template('quote.html')



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget user session
    session.clear()

    # User reached via POST method (submitting a form)
    if request.method == 'POST':

        # Ensure username and password was submitted, and also check if password was confirmed
        if not request.form.get('username'):
            return apology('Must provide a username', 400)

        elif not request.form.get('password'):
            return apology('Must provide a password', 400)

        elif not request.form.get('confirmation'):
            return apology('Must confirm the password', 400)

        # Check if password and confirmation match
        elif request.form.get('password') != request.form.get('confirmation'):
            return apology('Password and confirmation do not match', 400)

        # Query database for username and ensure username does not already exist
        rows = db.execute('SELECT * FROM users WHERE username = ?', request.form.get('username'))

        if len(rows) != 0:
            return apology('username already exist', 400)

        # Insert user into database
        db.execute('INSERT INTO users (username, hash) VALUES (?, ?)', request.form.get('username'), generate_password_hash(request.form.get('password')))

        # Query database for newly inserted user
        rows = db.execute('SELECT * FROM users WHERE username = ?', request.form.get('username'))

        # Remember which user has logged in
        session['user_id'] = rows[0]['id']

        # Redirect to home page
        return redirect('/')

    # User reached route via GET (clicking a link or via redirect)
    else:
        return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get users stocks
    stocks = db.execute('SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0', user_id=session['user_id'])

    if request.method == 'POST':
        symbol = request.form.get('symbol').upper()
        shares = request.form.get('shares')
        if not symbol:
            return apology('Must provide stock symbol')
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology('Must provide a positive integer as number of shares')
        else:
            shares = int(shares)

        for stock in stocks:
            if stock['symbol'] == symbol:
                if stock['total_shares'] < shares:
                    return apology('You do not have enough shares')
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology('Stock symbol not found')
                    price = quote['price']
                    total_sale = shares * price

                    # Update users table
                    db.execute('UPDATE users SET cash = cash + :total_sale WHERE id = :user_id', total_sale=total_sale, user_id=session['user_id'])

                    # Add transaction (sale) to history
                    db.execute('INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)', user_id=session['user_id'], symbol=symbol, shares=shares, price=price)

                    flash(f'Sold {shares} shares of {symbol} for {usd(total_sale)}')
                    return redirect('/')

        return apology('Stock symbol not found')

    # If the user visit the page
    else:
        return render_template('sell.html', stocks=stocks)

