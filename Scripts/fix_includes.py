import sys
import os

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument:', sys.argv[1]
print("Hello, world!")
for dirname, dirnames, filenames in os.walk(sys.argv[1]):
    for subdirname in dirnames:
        print os.path.join(dirname, subdirname)
    for filename in filenames:
        print os.path.join(dirname, filename)
