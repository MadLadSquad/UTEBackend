#pragma once
#include "Core/Defines.hpp"
#include "Core/Util.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <cstdarg>
#include <cerrno>
#include <cstring>

#ifndef _WIN32
    #ifdef __APPLE__
        #include <util.h>
    #else
        #include <pty.h>
    #endif
    #include <unistd.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/ioctl.h>
#else

#endif