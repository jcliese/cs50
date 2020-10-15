import csv
import sys
import re

#definition main function
def main():
    #check for right number of arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    else:
        #call open_csv function
        fields, rows = open_csv(sys.argv[1])
        str = []
        for field in fields:
            length_str, field = search_str(sys.argv[2], field)
            str.append(length_str)
        name = search_person(rows, str)
        print(f"{name}")

#definition of open_csv function
def open_csv(filename):
    fields = []
    persons =[]
    with open(filename, 'r') as csvfile:
        csvreader = csv.reader(csvfile)

        fields = next(csvreader)

        for row in csvreader:
            persons.append(row)

        return fields, persons

#definition of search function
def search_str(filename, seq):
    #open file
    with open(filename, 'r') as file:
        #read file into buffer
        data = file.read()
        #find indizes where sequence is in the data string
        indizes = [m.start() for m in re.finditer(seq, data)]
        max_str_length = 0
        for i in range(len(indizes)):
            str_length = 1
            for j in range(len(indizes[i:])-1):
                #increase str_length for every consecutive repetition of str sequence
                if (indizes[i + j] + len(seq)) == indizes[i+j+1]:
                    str_length += 1
                else:
                    break
            #check if a new max length is reached
            if str_length > max_str_length:
                max_str_length = str_length

        return max_str_length, seq

#definition of search function
def search_person(persons, str):
    for person in persons:
        for i in range(len(person)):
            #skip first column (name column)
            if i == 0:
                i += 1
                continue
            #check if last column is the same and return name of the person if true
            elif i == len(person)-1 and int(person[i]) == str[i]:
                return person[0]
            #check if column is same and continue with next column if true
            elif int(person[i]) == str[i]:
                i += 1
                continue
            #break out of loop if column is not same
            else:
                break
    return 'No match'

main()