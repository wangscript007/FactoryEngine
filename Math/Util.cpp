//
// Copyright (c) On5. All rights reserved.
//


#include "Util.h"

namespace Factory { namespace Util {

std::string Escape (const char* pszFormat)
{
    size_t l = strlen(pszFormat);
    std::string  s;
    for(int i = 0; i < l; i++)
        if(pszFormat[i] == '\\')
            i++;
        else if(pszFormat[i] == '@')
            s += "\\@";
        else
            s += pszFormat[i];
    return s;
}

std::string Number (int iNumber)
{
    std::stringstream ssText;
    ssText << iNumber;
    return ssText.str();
}

std::string Number (float fNumber)
{
    std::stringstream ssText;
    ssText << fNumber;
    return ssText.str();
}

std::string Number (double fNumber)
{
    std::stringstream ssText;
    ssText << fNumber;
    return ssText.str();
}

}}