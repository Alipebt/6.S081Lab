#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char *param[MAXARG];
    char bufn;
    char buf[1024];
    char *p = buf;
    int pid;

    memset(buf, 0, 1024);
    // param[]存入xargs后面的参数
    for (int i = 1; i < argc; i++)
    {
        param[i - 1] = argv[i];
    }

    while (read(0, &bufn, 1) > 0)
    {
        *p = bufn;
        if (*p == '\n')
        {
            *p = 0;

            param[argc - 1] = buf;

            pid = fork();
            if (pid == 0)
            {
                // chile
                exec(argv[1], param);
            }
            else
            {
                // pirent
                wait(0);
            }
        }

        ++p;
    }

    exit(0);
}