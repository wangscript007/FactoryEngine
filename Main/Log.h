//
// Copyright (c) 2012 On5. All rights reserved.
//
#pragma once

#ifdef DEBUG
    #define Log(flags, format, ...) Logf(__LINE__, __PRETTY_FUNCTION__, flags, format, ##__VA_ARGS__) 
#else
    #define Log(flags, format, ...) ((void)0)
#endif
//
// The values below are used as flags for different types of log messages.
//
typedef enum 
{
    // 32 bit
    kLog                 = 1 << 0,
    kLogMath             = 1 << 1,
    kLogEnvinroment      = 1 << 2,
    kLogModel            = 1 << 3,
    kLogWorkspace        = 1 << 4,
    kLogDocument         = 1 << 5,
    kLogView             = 1 << 6,
    kLogTool             = 1 << 7,
    kLogController       = 1 << 8,
    kLogApplication      = 1 << 9, 
} LogFlag;

extern unsigned int        logIfAny;
extern unsigned int        logIfAll;
extern bool                disableLogs;
extern bool                logEverything;

extern void                Logf(int line, const char* function, int flags, const char* format, ...);

