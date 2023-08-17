#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

using namespace std;

void p7b(int n)
{   
    for(int i = 0;i<n;i++)
    {
        if(!fork())
        {
            printf("Child %d is created\n", getpid());
            sleep(1);
            printf("Child %d of parent %d exited\n", getpid(), getppid());
            exit(0);
        }
    }
    return;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    printf("Parent is : %d\n", getpid());
    p7b(n);
    while(wait(NULL)>0){;}
    printf("Parent exited\n");
    return 0;
}