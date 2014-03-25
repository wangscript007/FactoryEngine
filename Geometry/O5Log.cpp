//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Manifest.h"

// change log filter by commenting/uncommenting 
O5Doubleword logIfAny = 
    O5LOG
    | 
    O5LOG_APPLICATION
    | 
    O5LOG_EVENTS
    | 
    O5LOG_NAVIGATION
    | 
    O5LOG_NETWORK
    | 
    O5LOG_FILE;

O5Doubleword    logIfAll                   = 0;
bool            disableLogs                = false;
bool            logEverything              = false;

void O5Logf(int line, const char* function, int flags, const char* format, ...)
{
	if (disableLogs) {
		return;
	}
	if (!logEverything) {
		if  (((logIfAny & flags) == 0) && (logIfAll == 0 || (logIfAll & flags) != logIfAll)) {
			return;
        }
	}
	va_list params_list;
	va_start(params_list, format);
    printf("%s ", function);
    printf(format, params_list);
    printf("\n");
	va_end(params_list);
}
