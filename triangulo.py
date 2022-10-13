import sys
i=0
l= int(input("quantidade de linhas : "))

for i  in range(0,l+1):
    r=l-i
    for r in range(-r,0):
        sys.stdout.write(" ")

    for y in range(1,i+i):
        
        sys.stdout.write("*")
    print("")


