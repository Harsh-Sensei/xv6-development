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
    int n = atoi(argv[1]);
    p2b(n);
    return 0;
}