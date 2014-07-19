# Finds all classes variables in file
import parsing

# print 'Argument:', sys.argv[1]
linestring = open('/Users/Edvinas/Dropbox/Factory/Source/FactoryEngine/Graph/FaceNode.h', 'r').read()
keywords = ['class', 'enum', 'struct', 'typedef']
parser = parsing.Parsing(linestring)
print parser.keywordBlock(keywords[0], '}')
for word in keywords:
    print word