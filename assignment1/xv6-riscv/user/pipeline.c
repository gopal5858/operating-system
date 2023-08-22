#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int n, x;
void print(int n, int x)
{
    int pipefd[2];
     if (pipe(pipefd) < 0)
    {
        printf("Error: cannot create pipe. Aborting...\n");
        exit(0);
    }
    
    if (n == 0)
    {
        // printf("%d : %d", getpid(), x);
        return;

    }
        if (fork() == 0)
        {
            
            // int p = getpid();
            
            // printf("%d : %d\n", getpid(), x);
            if (read(pipefd[0], &x, 4) < 0)
            {
                printf("Error: cannot read. Aborting...\n");
                exit(0);
            }
            x = x + getpid();
            if (write(pipefd[1], &x, 4) < 0)
            {
                printf("Error: cannot write. Aborting...\n");
                exit(0);
            }
            printf("%d : %d\n", getpid(), x);
            
            close(pipefd[0]);
            close(pipefd[1]);
        }
        else
        {
            // int w=0;

            if (write(pipefd[1], &x, 4) < 0)
            {
                printf("Error: cannot write. Aborting...\n");
                exit(0);
            }
            wait(NULL); 
            // int p = getpid();
            // x = x + p;
            if (read(pipefd[0], &x, 4) < 0)
            {
                printf("Error: cannot read. Aborting...\n");
                exit(0);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            print(n - 1, x);
        }
            
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Syntax: pipetest char. Aborting...\n");
        exit(0);
    }
   
    n = atoi(argv[1]);
    x = atoi(argv[2]);
    // printf("%d : %d\n", n, x);
    print(n,x);
    exit(0);
}