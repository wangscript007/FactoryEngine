//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Log.h"

// change log filter by commenting/uncommenting
unsigned int logIfAny = 
    kLog
//    |
//    kLogMath
//    |    
//    kLogEnvinroment
    |
    kLogModel
//    |
//    kLogWorkspace
    |
    kLogDocument
    |
    kLogView
    |
    kLogTool
    |
    kLogController
    | 
    kLogApplication
    ;

unsigned int    logIfAll                   = 0;
bool            disableLogs                = false;
bool            logEverything              = false;

void Logf(int line, const char* function, int flags, const char* format, ...)
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
    vprintf(format, params_list);
    printf("\n");
	va_end(params_list);
}
