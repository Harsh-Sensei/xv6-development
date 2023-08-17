#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

using namespace std;

void p7a(int n, bool is_parent)
{   
    // printf("%d\n", n);
    // fflush(stdout);
    if(n==0)
    {
        return;
    }
    if(is_parent)
    {
        return;
    }
    printf("Child %d is created\n", getpid());
    
    if(n == 1)
    {
        int cpid = fork();
        if(cpid == 0)
        {
            printf("Child %d is created\n", getpid());
            fflush(stdout);
            printf("Child %d with parent %d exited\n", getpid(), getppid());
            fflush(stdout);
            exit(0);
        }
        else
        {
            while(wait(NULL)>0){;}
            printf("Child %d of parent %d exited\n", getpid(), getppid());
            fflush(stdout);
            exit(0);
        }
    }
    // printf("Child %d is created\n", getpid());
    fflush(stdout);

    p7a(n-1,fork());
    while(wait(NULL)>0){;}
    printf("Child %d of parent %d exited\n", getpid(), getppid());
    fflush(stdout);
    exit(0);
    return;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    fflush(stdout);
    p7a(n-1, fork());
    while(wait(NULL)>0){;}
    return 0;
}