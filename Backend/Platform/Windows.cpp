#include "Windows.hpp"

#ifdef _WIN32
void UTE::WindowsBackend::init()
{

}

void UTE::WindowsBackend::update()
{

}

void UTE::WindowsBackend::cleanup()
{

}

std::string& UTE::WindowsBackend::getBuffer()
{
    return buffer;
}
#endif