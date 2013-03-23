#pragma once

#define FTDEBUG

#ifndef FT_DELETE
    #define FT_DELETE(a) { if(a) { delete (a); (a) = NULL; } }
#endif
