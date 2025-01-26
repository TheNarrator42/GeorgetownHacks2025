#assuming quine string location is marked with char*quineString=""; 
#and print location is marked with printf("quine");

program = input("enter .c file without extension: ")
preQuineString = ""
postQuineString = ""
preString = True
print(program+".c")
index = 0
PreQuineEsc = []
PostQuineEsc = []

content = open(program+".c", "r").read()
#print(content)
while index < len(content):
    char = content[index]
    #found a \, determine if its a new line indicator
    if(char == '\n'): 
        if(preString):
            PreQuineEsc.append("10")
            preQuineString += "%"
            preQuineString += "c"
        else:
            PostQuineEsc.append("10")
            postQuineString += "%"
            postQuineString += "c"
    elif(char == '\"'): #we need to exactly print out a quotatoin
        if(preString):
            PreQuineEsc.append("34")
            preQuineString += "%"
            preQuineString += "c"
        else:
            PostQuineEsc.append("34")
            postQuineString += "%"
            postQuineString += "c"
    else:
        if(preString):
            preQuineString += char
        else:
            postQuineString += char
    index += 1
    print(repr(char))

#properly insert itself
preQuineString = preQuineString.replace("char*quineString=%c%c", "char*quineString=%c%s%c")

breakPoint = preQuineString.find("char*quineString=%c%s%c")
PreQuineEsc.insert(preQuineString[0:breakPoint].count("%c")+1,"quineString")

newPrint = "printf(quineString"
endPrintbit = ");"

for s in PreQuineEsc:
    newPrint += "," + s
newPrint+= (endPrintbit)

preQuineString = preQuineString.replace("printf(%cquine%c);", newPrint)

print("helper quine string")
print("char*quineString=\"" + preQuineString + "\";")
print("new print statement")
print(newPrint)
