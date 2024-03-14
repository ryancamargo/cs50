from cs50 import get_string

# Get the text input from the user using get_string
text = get_string("Text: ")

# Counting the number of letters (e.g, not characters from a string)

letters = sum(i.isalpha() for i in text)

#print(letters)

# Counting the number of words

words = len(text.split())

#print(words)

# Counting the number of phrases - any occurrence of a period, exclamation point, or question mark indicates the end of a sentence

#letters = 0
#words = 1
sentences = 0
for i in range(len(text)):
    #if text[i].isalpha():
    #    letters += 1
    #elif text[i].isspace():
    #    words += 1
    if text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1

#print(letters)
#print(words)
#print(sentences)

# Calculating grade

L = letters * (100 / words)
S = sentences * (100 / words)

grade = round(0.0588 * L - 0.296 * S - 15.8)

#print(grade)

if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
