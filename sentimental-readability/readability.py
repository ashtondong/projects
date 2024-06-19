from cs50 import get_string


def main():

    text = get_string("Text: \n")

    # make sure to store the values as floats
    l = float(count_letters(text))
    w = float(count_words(text))
    s = float(count_sentences(text))

    # must be a float to get an accurate calculation
    L = float((l / w) * 100)
    S = float((s / w) * 100)

    # creating the Coleman-Liau index to calculate grade level
    # rounding to the nearest highest integer
    # store the float as an integer so there's no decimals
    # python will automatically truncate on integers
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index > 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {index}")


def count_letters(text):

    # creating a function to count letters
    count = 0
    length = len(text)

    for i in range(length):

        if (ord(text[i]) < 65 or ord(text[i]) > 90) and (ord(text[i]) < 97 or ord(text[i]) > 122):
            count = count + 0

        else:
            count += 1

    return count


def count_words(text):

    count = 0
    # split text into words, this produces a list of words

    words = text.split()
    # iterate through list of words, for each word, increase count

    for i in words:

        count += 1

    return count


def count_sentences(text):

    count = 0
    length = len(text)

    for i in range(length):

        if ord(text[i]) == 46 or ord(text[i]) == 33 or ord(text[i]) == 63:
            count += 1

        else:
            count = count + 0

    return count


main()