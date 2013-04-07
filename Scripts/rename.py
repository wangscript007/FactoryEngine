import sys
import os
import shutil

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument:', sys.argv[1]
for dirname, dirnames, filenames in os.walk(sys.argv[1]):
    #for subdirname in dirnames:
    # print os.path.join(dirname, subdirname)
    for filename in filenames:
        if filename.startswith(""):
            oldDir = dirname+"/"+filename
            newDir = dirname+"/"+filename[2:]
            print oldDir + "->" + newDir
            shutil.move(oldDir, newDir)