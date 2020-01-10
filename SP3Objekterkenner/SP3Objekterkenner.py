import sys
import os

print (sys.argv[1])
print (sys.argv[2])

filepath = os.path.abspath(sys.argv[2])
path = os.path.join(filepath, "gefundeneObjekte.txt")

print (path)
file = open(path,"w")

file.write(sys.argv[1])
#file.write("\n")
#file.write(sys.argv[2])
file.close
