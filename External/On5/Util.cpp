//
// Copyright (c) On5. All rights reserved.
//

#include <FactoryEngine.h>

using namespace std;

void O5ReplaceLetter (string& sStr, const string& target, const string& replacement) {
    unsigned int pos;

    while ((pos = sStr.find(target)) != string::npos) {
        sStr.replace (pos, 2, replacement);
    }
}

string O5ToAsciiString (const string& sStr) {
    string converted = sStr;

    O5ReplaceLetter (converted, "ä", "a");
    O5ReplaceLetter (converted, "á", "a");
    O5ReplaceLetter (converted, "à", "a");
    O5ReplaceLetter (converted, "ã", "a");
    O5ReplaceLetter (converted, "å", "a");
    O5ReplaceLetter (converted, "â", "a");
    O5ReplaceLetter (converted, "ą", "a");
    O5ReplaceLetter (converted, "ç", "c");
    O5ReplaceLetter (converted, "ć", "c");
    O5ReplaceLetter (converted, "č", "c");
    O5ReplaceLetter (converted, "é", "e");
    O5ReplaceLetter (converted, "è", "e");
    O5ReplaceLetter (converted, "ë", "e");
    O5ReplaceLetter (converted, "ê", "e");
    O5ReplaceLetter (converted, "ę", "e");
    O5ReplaceLetter (converted, "ė", "e");
    O5ReplaceLetter (converted, "í", "i");
    O5ReplaceLetter (converted, "ì", "i");
    O5ReplaceLetter (converted, "ï", "i");
    O5ReplaceLetter (converted, "î", "i");
    O5ReplaceLetter (converted, "į", "i");
    O5ReplaceLetter (converted, "ó", "o");
    O5ReplaceLetter (converted, "ò", "o");
    O5ReplaceLetter (converted, "õ", "o");
    O5ReplaceLetter (converted, "ô", "o");
    O5ReplaceLetter (converted, "ö", "o");
    O5ReplaceLetter (converted, "ø", "o");
    O5ReplaceLetter (converted, "ú", "u");
    O5ReplaceLetter (converted, "ù", "u");
    O5ReplaceLetter (converted, "ü", "u");
    O5ReplaceLetter (converted, "û", "u");
    O5ReplaceLetter (converted, "ų", "u");
    O5ReplaceLetter (converted, "ū", "u");
    O5ReplaceLetter (converted, "ÿ", "y");
    O5ReplaceLetter (converted, "ß", "ss");
    O5ReplaceLetter (converted, "ś", "s");
    O5ReplaceLetter (converted, "š", "s");
    O5ReplaceLetter (converted, "ź", "z");
    O5ReplaceLetter (converted, "ż", "z");
    O5ReplaceLetter (converted, "ž", "z");
    O5ReplaceLetter (converted, "œ", "oe");
    O5ReplaceLetter (converted, "æ", "ae");
    O5ReplaceLetter (converted, "ñ", "n");
    O5ReplaceLetter (converted, "ń", "n");
    O5ReplaceLetter (converted, "ł", "l");
    
    return converted;
}

string O5Format (const char* pszFormat, ...)
{
    int     l = strlen(pszFormat);
    va_list v;
    string  s;
    va_start(v, pszFormat);
    for(int i = 0; i < l; i++)
        if(pszFormat[i] == '\\')
            i++;
        else if(pszFormat[i] == '@')
            s += va_arg(v, const char*);
        else
            s += pszFormat[i];
    va_end(v);
    return s;
}

string O5Escape (const char* pszFormat)
{
    int     l = strlen(pszFormat);
    string  s;
    for(int i = 0; i < l; i++)
        if(pszFormat[i] == '\\')
            i++;
        else if(pszFormat[i] == '@')
            s += "\\@";
        else
            s += pszFormat[i];
    return s;
}

string O5Number (int iNumber)
{
    std::stringstream ssText;
    ssText << iNumber;
    return ssText.str();
}

string O5Number (float fNumber)
{
    std::stringstream ssText;
    ssText << fNumber;
    return ssText.str();
}

string O5Number (double fNumber)
{
    std::stringstream ssText;
    ssText << fNumber;
    return ssText.str();
}