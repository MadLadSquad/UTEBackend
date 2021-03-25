#include "Backend/Backend.hpp"
#include <ctime>


template<typename... args>
void runCmd(const char* cmd, args&&... argv)
{
    execlp(cmd, cmd, argv..., nullptr);


}

int main()
{
    auto pid = forkpty(&fd, nullptr, nullptr, &ws);

    if(!pid)
    {
        static char termstr[] = "TERM=xterm";
        putenv(termstr);
        execl(std::getenv("SHELL"), std::getenv("SHELL"), "-l", "-i", nullptr);
    }
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);


    /*//execlp("tty", "tty");
    auto ptfd = posix_openpt(O_RDWR | O_NOCTTY);

    if (ptfd != -1)
    {
        printf("ptfd works\n");
    }
    else
    {
        return -1;
    }
    grantpt(ptfd);
    unlockpt(ptfd);

    auto ptname = ptsname(ptfd);

    printf("Name is %s", ptname);

    std::string a;
    std::cin >> a;
    int pid = fork();

    if (pid == -1)
    {
        return -1;
    }

    if (pid == 0)
    {
        runCmd("bash");
    }
    else
    {
        wait(nullptr);

        std::cout << "Yes" << std::endl;
    }
    return 0;*/
}