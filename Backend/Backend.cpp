#include "Backend.hpp"

void UTE::Backend::init()
{
    backend.init();
}

void UTE::Backend::update()
{
    backend.update();
}

void UTE::Backend::cleanup()
{
    backend.cleanup();
}

std::string& UTE::Backend::getBuffer()
{
    return backend.getBuffer();
}
