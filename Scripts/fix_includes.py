import sys
import os

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument:', sys.argv[1]
print("Hello, world!")
for dirname, dirnames, filenames in os.walk(sys.argv[1]):
    for subdirname in dirnames:
        print os.path.join(dirname, subdirname)
    for filename in filenames:
        substring = filename[0:2]
        if substring == "" :
            print filename
