#assuming quine string location is marked with QUINE_STRING
#and print location is marked with QUINE_PRINTF_ARGS

from sys import argv

if len(argv) == 2:
  program = argv[1]
else:
  program = input("enter .c file without extension: ")
preQuineString = ""
print(program+".c")
index = 0
PreQuineEsc = []

content = open(program+".c", "r").read()
#print(content)
while index < len(content):
    char = content[index]
    print(repr(char))
    #found a \, determine if its a new line indicator
    if(char == '\n'): 
        PreQuineEsc.append("10")
        print(PreQuineEsc)
        preQuineString += "%"
        preQuineString += "c"
    elif(char == '\"'): #we need to exactly print out a quotatoin
        PreQuineEsc.append("34")
        print(PreQuineEsc)
        preQuineString += "%"
        preQuineString += "c"
    elif(char == '\\'): #meta character, panik?
        PreQuineEsc.append("92")
        print(PreQuineEsc)
        preQuineString += "%"
        preQuineString += "c"
    else:
        preQuineString += char
    index += 1

PreQuineEsc.insert(preQuineString[0:preQuineString.find("QUINE_STRING")].count("%c"),"34")
PreQuineEsc.insert(preQuineString[0:preQuineString.find("QUINE_STRING")].count("%c"),"34")
breakPoint = preQuineString.find("QUINE_STRING")
#properly insert itself
preQuineString = preQuineString.replace("QUINE_STRING", "%c%s%c")
PreQuineEsc.insert(preQuineString[0:breakPoint].count("%c")+1,"quineString")

newPrint = "quineString"

for s in PreQuineEsc:
    newPrint += "," + s

preQuineString = preQuineString.replace("QUINE_PRINTF_ARGS", newPrint)

print("helper quine string")
print("char*quineString=\"" + preQuineString + "\";")
print("new print statement")
print(newPrint)

content = open(program+".c", "r").read()

content = content.replace("QUINE_STRING", "\""+preQuineString+"\"")
content = content.replace("QUINE_PRINTF_ARGS", newPrint)

writer = open(program+"quine"+".c", "w").write(content)

