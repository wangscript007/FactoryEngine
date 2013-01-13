//
// Copyright (c) On5. All rights reserved.
//


#include "Util.h"

using namespace std;

string O5Escape (const char* pszFormat)
{
    size_t l = strlen(pszFormat);
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