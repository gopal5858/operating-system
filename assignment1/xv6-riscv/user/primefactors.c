#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int n, prime[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

void primefact(int n,int index)
{
    int pipefd[2];
     if (pipe(pipefd) < 0)
    {
        printf("Error: cannot create pipe. Aborting...\n");
        exit(0);
    }
    
    if (index == 25)
    {
        return;
    }
        if (fork() == 0)
        {
            

            if (read(pipefd[0], &n, 4) < 0)
            {
                printf("Error: cannot read. Aborting...\n");
                exit(0);
            }
            if(n%prime[index]==0){
                while(n%prime[index]==0){
                    printf("%d ",prime[index]);
                    n = n/prime[index];
                }
                printf("[%d]\n",getpid());
            }
            if (write(pipefd[1], &n, 4) < 0)
            {
                printf("Error: cannot write. Aborting...\n");
                exit(0);
            }

            
            close(pipefd[0]);
            close(pipefd[1]);
        }
        else
        {

            if (write(pipefd[1], &n, 4) < 0)
            {
                printf("Error: cannot write. Aborting...\n");
                exit(0);
            }
            wait(NULL); 
            if (read(pipefd[0], &n, 4) < 0)
            {
                printf("Error: cannot read. Aborting...\n");
                exit(0);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            primefact(n, index+1);
        }
            
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Syntax: pipetest char. Aborting...\n");
        exit(0);
    }
   
    n = atoi(argv[1]);
    // printf("%d : %d\n", n, x);
    primefact(n,0);
    exit(0);
}