//
// Copyright (c) 2012 On5. All rights reserved.
//
#ifdef FTDEBUG 
    #define FTLog(flags, format, ...) FTLogf(__LINE__, __PRETTY_FUNCTION__, flags, format, ##__VA_ARGS__) 
#else
    #define FTLog(flags, format, ...) ((void)0)
#endif
//
// The values below are used as flags for different types of log messages.
//
typedef enum 
{
    // 32 bit
    kFTLog                 = 1 << 0,
    kFTLogMath             = 1 << 1,
    kFTLogEnvinroment      = 1 << 2,
    kFTLogModel            = 1 << 3,
    kFTLogWorkspace        = 1 << 4,
    kFTLogDocument         = 1 << 5,
    kFTLogView             = 1 << 6,
    kFTLogTool             = 1 << 7,
    kFTLogController       = 1 << 8,
    kFTLogApplication      = 1 << 9, 
} FTLogFlag;

extern unsigned int        logIfAny;
extern unsigned int        logIfAll;
extern bool                disableLogs;
extern bool                logEverything;

extern void                FTLogf(int line, const char* function, int flags, const char* format, ...);

