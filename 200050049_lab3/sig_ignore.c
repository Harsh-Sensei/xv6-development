#include<stdio.h>
#include<signal.h>


void sigint_handler(int sig)
{
    printf("Sigint\n");
    return;
}

void sigterm_handler(int sig)
{
    printf("Sigterm\n");
    return;
}

int main(int args, char* argv[])
{
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigterm_handler);
    printf("Process Id is: %d\n", getpid());

    while(1)
    {
        printf("Waiting...\n");
        sleep(3);        
    }

    return 0;
}