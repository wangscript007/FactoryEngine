import sys
import os
import array
from pyparsing import nestedExpr

class Parsing:
    def __init__(self, text):
        self.text = text;
    
    def findNext(self, text, fromIndex):
        return '';
    
    def closingBracket(self, fromIndex):
        return '';
    
    def keyworkdBlock(self, keyword):
        index1 = self.text.find(keyword) + len(keyword)
        return index1

