#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void p6b()
{
    int parent = fork();

    if(parent)
    {
        printf("Parent : My process ID is:%d\n",getpid());
        printf("Parent : The child process ID is:%d\n", parent);
        sleep(60);
    }
    else
    {
        printf("Child : My process ID is:%d\n", getpid());
        printf("Child : The parent process ID is:%d\n", getppid());
        
        printf("Child : Check child process state\n");
        printf("Child : Press any key to continue\n");
        getchar();
        printf("Child : Check child process state again\n");
    }

    return;
}

int main(int argc, char* argv[])
{
    p6b();
    return 0;
}