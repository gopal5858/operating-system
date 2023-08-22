#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int n, m;
    if (argc != 3)
    {
        printf("Syntax: forkleeptest char. Aborting...\n");
        exit(0);
    }
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    int b;
    b = fork();
    if (n == 0)
    {
        if (b < 0)
        {
            printf("Error in fork. Aborting...\n");
            exit(0);
        }
        if (b == 0)
        {
            sleep(m);
            printf("%d: Child\n", getpid());
            exit(0);
        }
        printf("%d: Parent\n", getpid());
    }
    else
    {
        if (b < 0)
        {
            printf("Error in fork. Aborting...\n");
            exit(0);
        }
        if (b == 0)
        {
            printf("%d: Child\n", getpid());
            exit(0);
        }
        sleep(m);
        printf("%d: Parent\n", getpid());
    }
    exit(0);
}