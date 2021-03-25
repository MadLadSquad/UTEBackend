#include "Backend/Backend.hpp"
#include <ctime>

template<typename... args>
void runCmd(const char* cmd, args&&... argv)
{
    execlp(cmd, cmd, argv..., nullptr);
}

int main()
{
    std::string a;
    std::cin >> a;
    int pid = fork();

    if (pid == -1)
    {
        return -1;
    }

    if (pid == 0)
    {
        runCmd("ping", "google.com");
    }
    else
    {
        wait(nullptr);

        std::cout << "Yes" << std::endl;
    }
    return 0;
}