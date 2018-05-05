#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int
Open_File(void)
{
    const char *fileName = "data/file1.txt";
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int flag = O_WRONLY | O_CREAT | O_SYNC;
    int fd = 0;

    fd = open(fileName, flag, mode);
    if (fd < 0)
    {
        printf("Failed to open file %s\n", fileName);
        return -1;
    }

    return fd;
}

int
Run_AppendWriteTest(int fd)
{
    int ret = -1;
    const int loop_count = 10000;
    int i = 0;
    char *buff = NULL;
    size_t len = 5*1024;
    size_t l1  = 0;

    buff = malloc(len);
    if (buff == NULL)
    {
        goto out;
    }

    memset(buff, '=', len - 2);
    buff[len - 1] = '\n';

    for (i = 0; i < loop_count; ++i)
    {
        l1 = write(fd, buff, len);
        if (l1 != len)
        {
            printf("Failed to write complete content: %lu/%lu\n", l1, len);
            goto out;
        }
    }

    ret = 0;
out:
    if (buff)
    {
        free(buff);
    }
    return ret;
}

int
Run_AppendTruncateTest(int fd)
{
    int ret = -1;
    const int loop_count = 10;
    int i = 0;
    char *buff = NULL;
    size_t len = 5*1024;
    size_t l1  = 0;

    buff = malloc(len);
    if (buff == NULL)
    {
        goto out;
    }

    memset(buff, '=', len - 2);
    buff[len - 1] = '\n';

    for (i = 0; i < loop_count; ++i)
    {
        l1 = write(fd, buff, len);
        if (l1 != len)
        {
            printf("Failed to write complete content: %lu/%lu\n", l1, len);
            goto out;
        }
        ret = ftruncate(fd, i); 
    }

    ret = 0;
out:
    if (buff)
    {
        free(buff);
    }
    return ret;
}

int
TestFunction(void)
{
    int ret = 0;
    int fd = 0;

    fd = Open_File();
    if (fd < 0)
    {
        return -1;
    }

    ret = Run_AppendWriteTest(fd);
    ret = Run_AppendTruncateTest(fd);

    close(fd);

    return ret;
}

int main()
{
    int ret = 0;

    ret = TestFunction();

    return ret;
}
