#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void p6a()
{
    int parent = fork();

    if(parent)
    {
        printf("Parent : My process ID is:%d\n",getpid());
        printf("Parent : The child process ID is:%d\n", parent);
    }
    else
    {
        printf("Child : My process ID is:%d\n", getpid());
        printf("Child : The parent process ID is:%d\n", getppid());
        sleep(5);
        printf("Child : After sleeping for 5 seconds\n");
        printf("Child : My process ID is:%d\n", getpid());
        printf("Child : The parent process ID is:%d\n", getppid());
    }

    return;
}

int main(int argc, char* argv[])
{
    p6a();
    return 0;
}