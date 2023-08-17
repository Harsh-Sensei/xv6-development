#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

using namespace std;

void p2b(int n)
{
    int parent = fork();

    if(parent)
    {   
        while(wait(NULL)>0){;}
        for(int i=n+1;i<=2*n;i++)
        {
            printf("P %d %d\n",getpid(), i);
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            printf("C %d %d\n",getpid(), i);
        }
    }

    return;
}

int main(int argc, char* argv[])
{   
    while(true)
    {
        printf(">>>");
        char buff[50];
        scanf("%s", buff);
        if(!fork())
        {   
            char new_buff[52];
            sprintf(new_buff, "./%s", buff);
            char* args[] = {new_buff, NULL};
            execvp(args[0], args);
            
            exit(0);
        }
        sleep(1);
        printf("\n");
    }
    return 0;
}