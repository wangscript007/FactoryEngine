//
// Copyright (c) 2012 On5. All rights reserved.
//



// The values below are used as flags for different types of log messages.
typedef enum 
{
    // 32 bit
    O5LOG                   = 1 << 0,
	O5LOG_APPLICATION       = 1 << 1,
    O5LOG_EVENTS 			= 1 << 3,
    O5LOG_NAVIGATION        = 1 << 4,
    O5LOG_NETWORK           = 1 << 5,
    O5LOG_FILE              = 1 << 6
} O5LOG_FLAG;

extern O5Doubleword        logIfAny;
extern O5Doubleword        logIfAll;
extern bool                disableLogs;
extern bool                logEverything;

extern void                O5Logf(int line, const char* function, int flags, const char* format, ...);

