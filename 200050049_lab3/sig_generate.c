#include<stdio.h>
#include<signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int args, char* argv[])
{
    if(args != 2)
    {
        printf("Error: Invalid command line arguments\n");
        exit(0);
    }
    int pid = atoi(argv[1]);
    kill(pid, SIGINT);
    printf("SIGINT signal sent to PID: %d", pid);
    sleep(1);
    kill(pid, SIGTERM);
    printf("SIGTERM signal sent to PID: %d", pid);
    sleep(1);
    kill(pid, SIGKILL);
    printf("SIGKILL signal sent to PID: %d", pid);

    return 0;
}