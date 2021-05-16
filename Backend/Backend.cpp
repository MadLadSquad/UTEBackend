#include "Backend.hpp"

pid_t UnixBackend::ptyFork(int* masterFd, char* slaveName, size_t snLen, const struct termios* slaveTermios, const struct winsize* slaveWS)
{
    int mfd, slaveFd, savedErrno;
    pid_t childPid;
    char slname[1000];

    mfd = ptyMasterOpen(slname, 1000);

    if (slaveName != nullptr)
    {
        if (strlen(slname) < snLen)
        {
            strncpy(slaveName, slname, snLen);
        }
        else
        {
            close(mfd);
            errno = EOVERFLOW;
            return -1;
        }
    }

    childPid = fork();

    if (childPid == -1)
    {
        savedErrno = errno;
        close(mfd);
        errno = savedErrno;
        return -1;
    }

    if (childPid != 0)
    {
        *masterFd = mfd;
        return childPid;
    }

    setsid();
    close(mfd);

    slaveFd = open(slname, O_RDWR);

#ifdef TIOCSCTTY
    ioctl(slaveFd, TIOCSCTTY, 0);
#endif

    if (slaveTermios != nullptr)
    {
        tcsetattr(slaveFd, TCSANOW, slaveTermios);
    }

    if (slaveWS != nullptr)
    {
        ioctl(slaveFd, TIOCSWINSZ, slaveWS);
    }

    dup2(slaveFd, STDIN_FILENO);
    dup2(slaveFd, STDOUT_FILENO);
    dup2(slaveFd, STDERR_FILENO);

    if (slaveFd > STDERR_FILENO) close(slaveFd);

    return 0;
}

int UnixBackend::ptyMasterOpen(char* slaveName, size_t snLen)
{
    int masterFd, savedErrno;
    char* p;

    masterFd = posix_openpt(O_RDWR | O_NOCTTY);
    if (masterFd == -1)
        return -1;

    if (grantpt(masterFd) == -1)
    {
        savedErrno = errno;
        close(masterFd);
        errno = savedErrno;
        return -1;
    }

    if (unlockpt(masterFd) == -1)
    {
        savedErrno = errno;
        close(masterFd);
        errno = savedErrno;
        return -1;
    }

    p = ptsname(masterFd);
    if (p == nullptr)
    {
        savedErrno = errno;
        close(masterFd);
        errno = savedErrno;
        return -1;
    }

    if (strlen(p) < snLen)
    {
        strncpy(slaveName, p, snLen);
    }
    else
    {
        close(masterFd);
        errno = EOVERFLOW;
        return -1;
    }

    return masterFd;
}

int UnixBackend::ttySetRaw(int fd, struct termios *prevTermios)
{
    struct termios t{};

    if (tcgetattr(fd, &t) == -1)
        return -1;

    if (prevTermios != nullptr) *prevTermios = t;

    t.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
    t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INLCR | INPCK | ISTRIP | IXON | PARMRK);
    t.c_oflag &= ~OPOST;
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSAFLUSH, &t) == -1) return -1;

    return 0;
}

void ttyReset()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &ttyOrig);
}

void UnixBackend::update()
{
    FD_ZERO(&inFds);
    FD_SET(STDIN_FILENO, &inFds);
    FD_SET(masterFd, &inFds);

    select(masterFd + 1, &inFds, nullptr, nullptr, nullptr);

    if (FD_ISSET(STDIN_FILENO, &inFds))
    {
        numRead = read(STDIN_FILENO, buf, 256);
        if (numRead <= 0)
            exit(EXIT_SUCCESS);

        write(masterFd, buf, numRead);
    }

    if (FD_ISSET(masterFd, &inFds))
    {
        numRead = read(masterFd, buf, 256);
        if (numRead <= 0)
            exit(EXIT_SUCCESS);

        buffer.append(buf, numRead);
    }
}

void UnixBackend::init()
{
    tcgetattr(STDIN_FILENO, &ttyOrig);
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

    childPid = ptyFork(&masterFd, slaveName, 1000, &ttyOrig, &ws);

    if (childPid == 0)
    {
        shell = getenv("SHELL");
        if (shell == nullptr || *shell == '\0')
            shell = (char*)"/bin/sh\0";

        execlp(shell, shell, (char*) nullptr);
    }

    ttySetRaw(STDIN_FILENO, &ttyOrig);
    std::atexit(ttyReset);
}

void UnixBackend::cleanup() const
{
    write(STDIN_FILENO, "exit", 4);
    close(masterFd);
}
