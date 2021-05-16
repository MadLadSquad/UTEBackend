#pragma once

// copied from TLPI
#if ! defined(__sun)
    #if ! defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 600
        #define _XOPEN_SOURCE 600
    #endif
#endif

#if defined(__sun)
    #define NO_POSIX_OPENPT
#endif

#ifdef NO_POSIX_OPENPT
static int posix_openpt(int flags)
{
    return open("/dev/ptmx", flags);
}
#endif
#if ! defined(__hpux)
    #include <sys/select.h>
#endif