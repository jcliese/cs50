from cs50 import get_string
import re

def main():
    numb = get_user_input()
    check_card(numb)

#ask user for credit card number
def get_user_input():
    numb = get_string("Number: ")
    return numb

def check_card(numb):
    #return true or false
    credit_card = luhn(numb)
    #check for amex
    if re.search("^3[47]\d{13}$", numb) and credit_card:
        print("AMEX")
    #check for mastercard
    elif re.search("^5[1-5]\d{14}$", numb) and credit_card:
        print("MASTERCARD")
    #check for visa
    elif (re.search("^4\d{12}$", numb) or re.search("^4\d{15}$", numb)) and credit_card:
        print("VISA")
    #output for invalid credit card number
    else:
        print("INVALID")

#check if it is a credit card
def luhn(input):
    i = len(input)-2
    j = len(input)-1
    sum = 0
    while i >= 0:
        t = int(input[i])*2
        while t:
            sum += t % 10
            t //= 10
        i -= 2
    while j >= 0:
        sum += int(input[j])
        j -= 2
    print(f"SUM: {sum}")
    if sum % 10 == 0:
        return True
    return False

#call main function
main()