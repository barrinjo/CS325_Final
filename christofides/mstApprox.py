import sys
import re

if len(sys.argv) == 2:
    # open file from argv
    try:
        file = open(sys.argv[1], "r")
    # exit with error if file not found
    except:
        print("No file named \"{}\" found".format(sys.argv[1]))
        quit()
# if incorrect number of args, print command format
else :
    print("usage: \"python3 mstEuclid.py <filename.txt>\"")
    quit()

forest = []

line = file.readline()
while line:
    temp = re.findall(r'\d+', line) 
    res = list(map(int, temp)) 
    print(res)
    line = file.readline()

