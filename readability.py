from cs50 import get_string
import re

#call of the main function
def main():
    #get user input
    input = get_string("Text: ")
    #call letter count function
    letters = count_letters(input)
    #call word count function
    words = count_words(input)
    #call sentence count function
    sentence = count_sentence(input)
    coleman_lieu = calc(letters, words, sentence)
    print(f"{grade(coleman_lieu)}")

#count letters in text
def count_letters(input):
    #filter for only alphabetical chars
    letters = len(''.join(filter(str.isalpha, input)))
    return letters

def count_words(input):
    #count words by searching for whitespaces
    words = input.count(' ') + 1
    return words

def count_sentence(input):
    #count sentences by searching for ., ! and ?
    sentence = 0
    sentence += input.count('.')
    sentence += input.count('!')
    sentence += input.count('?')
    return sentence

def calc(letters, words, sentences):
    #calculate the coleman lieu score
    l = letters / words * 100
    s = sentences / words * 100
    return 0.0588 * l - 0.296 * s - 15.8

def grade(coleman_lieu):
    #generate the output according to coleman lieu score
    cl = round(coleman_lieu)
    if cl > 16:
        return 'Grade 16+'
    elif cl < 1:
        return "Before Grade 1"
    else:
        return f"Grade {cl}"

#call main function
main()