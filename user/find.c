#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define BUFSIZE 512

char *fmtname(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;
    for (p = path + strlen(path); p > path && *p != '/'; p--)
        ;
    ++p;

    if (strlen(p) >= DIRSIZ)
    {
        return p;
    }

    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
    return buf;
}

void find(char *path, char *name)
{
    int fd;
    char buf[BUFSIZE], namebuf[DIRSIZ + 1], *p;
    struct stat info;
    struct dirent dir;

    memmove(namebuf, name, strlen(name));
    memset(namebuf + strlen(name), ' ', DIRSIZ - strlen(name));

    if ((fd = open(path, 0)) < 0)
    {
        printf("find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &info) < 0)
    {
        printf("find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (info.type != T_DIR)
    {
        printf("find: 必须是一个目录");
        exit(1);
    }

    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
    {
        printf("find: path too long\n");
        close(fd);
        exit(1);
    }

    strcpy(buf, path);
    p = buf + strlen(path);
    *p++ = '/';
    while (read(fd, &dir, sizeof(dir)) == sizeof(dir))
    {
        if (dir.inum == 0)
        {
            continue;
        }
        memmove(p, dir.name, DIRSIZ);
        p[DIRSIZ] = '\0';
        if (stat(buf, &info) < 0)
        {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        if (info.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0)
        {
            find(buf, name);
        }
        else if (strcmp(fmtname(buf), namebuf) == 0)
        {
            printf("%s/%s\n", path, name);
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("find: 参数不正确");
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}