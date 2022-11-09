#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define PRIME 35

void Child(int pfd[2], int cull)
{

    close(pfd[1]);

    int pfd2[2];
    pipe(pfd2);
    int pid;

    int buf;
    int ccull = -1;
    if (ccull != -1)
    {
        return;
    }
    //接收到的i第一个数必定为素数
    if (read(pfd[0], &buf, sizeof(buf)) > 0)
    {
        printf("prime %d\n", buf);
    }
    //从第二个数开始发送
    if (read(pfd[0], &buf, sizeof(buf)) > 0)
    {
        ccull = buf;
        write(pfd2[1], &buf, sizeof(buf));
    }

    if ((pid = fork()) < 0)
    {
        printf("ERROR");
        exit(1);
    }
    else if (pid > 0)
    {
        // parent
        while (read(pfd[0], &buf, sizeof(buf)) > 0)
        {
            if (buf % cull != 0)
            {
                write(pfd2[1], &buf, sizeof(buf));

                // wait(0);
            }
        }
        close(pfd2[1]);
        close(pfd[0]);
        wait(0);
    }
    else if (ccull != -1)
    {
        // child
        Child(pfd2, ccull);
    }
    exit(0);
}

int main()
{
    int pfd[2];
    int pid;
    int cull = 2;

    pipe(pfd);

    if ((pid = fork()) < 0)
    {
        printf("ERROR");
        exit(1);
    }
    else if (pid > 0)
    {
        // parent
        for (int i = 2; i <= PRIME; i++)
        {
            if (write(pfd[1], &i, sizeof(i)) <= 0)
            {
                i--;
            }
        }
        close(pfd[1]);
        wait(0);
    }
    else
    {
        // child
        Child(pfd, cull);
    }
    exit(0);
}