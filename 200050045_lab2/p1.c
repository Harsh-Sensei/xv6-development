#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void p1()
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
    }

    return;
}

int main(int argc, char* argv[])
{
    p1();
    return 0;
}