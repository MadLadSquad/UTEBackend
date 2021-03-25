#pragma once
#include "Core.hpp"

enum PROCESS_TYPE
{
    PARENT,
    CHILD
};

class Comms
{
public:
    Comms()
    {

    }

    [[maybe_unused]] void executeFunction(PROCESS_TYPE type, std::function<void(void)> func);


private:
    int p1[2];
    int p2[2];
};


