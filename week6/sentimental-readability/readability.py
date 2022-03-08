# Ask the user for a text
text = input("Text: ")

# calculate the length of the text for the loops
length = len(text)

# Letter count
count_letter = 0
for i in range(length):
    if text[i].isalpha() == True:
        count_letter += 1
num_letters = count_letter

# Word count
count_word = 0
for j in range(length):
    if text[j] == " ":
        count_word += 1
num_words = count_word + 1

# Sentence count
count_sentences = 0
for k in range(length):
    if text[k] == "." or text[k] == "?" or text[k] == "!":
        count_sentences += 1
num_sentences = count_sentences

# Calculate L & S for the Coleman_Liau index calculation
L = num_letters/num_words * 100
S = num_sentences/num_words * 100

# Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)

# Printing result
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")