import sys
from cs50 import SQL

def main():
    #check for right amount of arguments
    if len(sys.argv) != 2:
        print("Usage: python roster.py Gryffindor")
        sys.exit(1)
    else:
        #db connection
        db = SQL("sqlite:///students.db")

        house = sys.argv[1]

        #execute SQL
        names = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)
        for name in names:
            #check for middle name
            if name["middle"] is not None:
                print(f"{name['first']} {name['middle']} {name['last']}, born {name['birth']}")
            else:
                print(f"{name['first']} {name['last']}, born {name['birth']}")

main()
