import sys

print (sys.argv[1])
print (sys.argv[2])

file = open("helloworld.txt","w")

file.write(sys.argv[1])
file.write("\n")
file.write(sys.argv[2])

file.close
