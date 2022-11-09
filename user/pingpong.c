#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUFSIZE 255
int main()
{
    int ptoc[2], ctop[2];
    pipe(ptoc), pipe(ctop);
    char buf[BUFSIZE];

    if (fork() > 0) // parent
    {
        close(ptoc[0]);
        close(ctop[1]);
        write(ptoc[1], "ping", BUFSIZE);
        wait(0);
        if (read(ctop[0], buf, BUFSIZE) > 0)
        {
            fprintf(1, "%d: received %s\n", getpid(), buf);
        }
    }
    else // child
    {
        close(ptoc[1]);
        close(ctop[0]);
        if (read(ptoc[0], buf, BUFSIZE) > 0)
        {
            close(ptoc[0]);
            fprintf(1, "%d: received %s\n", getpid(), buf);
            write(ctop[1], "pong", BUFSIZE);
            close(ctop[1]);
        }
    }
    exit(0);
}