#pragma once

#define FT_DEBUG

#ifndef FT_DELETE
    #define FT_DELETE(a) { if(a) { delete (a); (a) = NULL; } }
#endif
