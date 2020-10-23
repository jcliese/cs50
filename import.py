import csv
import sys
from cs50 import SQL

def main():
    #check for right amount of arguments
    if len(sys.argv) != 2:
        print("Usage: python import.py characters.csv")
        sys.exit(1)
    else:
        #db connection
        db = SQL("sqlite:///students.db")
        filename = sys.argv[1]

        fields = []
        rows = []
        id = 0

        #open csv reader
        with open(filename, 'r') as character_csv:
            csvreader = csv.reader(character_csv)

            fields = next(csvreader)

            #append rows
            for row in csvreader:
                rows.append(row)

            for row in rows:
                name_arr = row[0]
                #split name in first, middle and last
                first, *middle, last = name_arr.split(' ', 3)
                middle = None if not middle else middle[0]
                #insert into db
                db.execute("INSERT INTO students VALUES (?,?,?,?,?,?)", id, first, middle, last, row[1], row[2])
                id += 1


main()
