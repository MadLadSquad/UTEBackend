#pragma once
#include <Core.hpp>

#ifdef _WIN32
namespace UTE
{
    class WindowsBackend
    {
    public:
        WindowsBackend() = default;

        void init();
        void update();
        void cleanup();

        std::string& getBuffer();
    private:
        std::string buffer;

    };
}
#endif