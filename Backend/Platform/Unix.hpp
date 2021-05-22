#pragma once
#include "../Core.hpp"

#ifndef _WIN32
namespace UTE
{
    class UnixBackend
    {
    public:
        UnixBackend() = default;

        std::string& getBuffer()
        {
            return buffer;
        }

        void init();
        void update();
        void cleanup();
        void sendCommand(std::string& command);

        int& getMaster()
        {
            return masterFd;
        }
    private:
        static int ttySetRaw(int fd, struct termios *prevTermios);
        static int ptyMasterOpen(char* slaveName, size_t snLen);
        static pid_t ptyFork(int *masterFd, char *slaveName, size_t snLen, const struct termios *slaveTermios, const struct winsize *slaveWS);

        void ttyReset();

        std::string buffer;

        char slaveName[1000]{};
        char* shell{};
        int masterFd{};
        winsize ws{};
        fd_set inFds{};
        char buf[256]{};
        ssize_t numRead{};
        pid_t childPid{};
        termios ttyOrig{};
        size_t error = 0;
    };
}
#endif
