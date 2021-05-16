#pragma once
#include "Core.hpp"

static void ttyReset();

inline termios ttyOrig{};

class Comms
{
public:
    Comms(int argc, char** argv);

    std::string& getBuffer()
    {
        return buffer;
    }
private:
    static int ttySetRaw(int fd, struct termios *prevTermios);
    static int ptyMasterOpen(char* slaveName, size_t snLen);
    static pid_t ptyFork(int *masterFd, char *slaveName, size_t snLen, const struct termios *slaveTermios, const struct winsize *slaveWS);

    std::string buffer;
};


