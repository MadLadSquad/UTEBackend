#pragma once
#include <Core.hpp>

#ifndef _WIN32
    #include "Platform/Unix.hpp"
#else
    #include "Platform/Windows.hpp"
#endif

namespace UTE
{
    class Backend
    {
    public:
        void init();
        void update();
        void cleanup();

        std::string& getBuffer();
    private:
#ifndef _WIN32
        UnixBackend backend;
#else
        WindowsBackend backend;
#endif
    };
}