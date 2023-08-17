#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <string.h>

using namespace std;


int main(int argc, char* argv[])
{  
    int p1[2]; 
    pipe(p1);
    printf("Read File Descriptor Value 1: %d\n", p1[0]);
    printf("Write File Descriptor Value 1: %d\n", p1[1]);
    int child_pid = fork();
    if(!child_pid)
    {
        int p2[2];
        pipe(p2);
        int childb = fork();
        if(childb)
        {
            char f1 = '$';
            char input1[50];
            int i = 0;
            while(f1 != '\0' && f1 != '\n' && f1 != ' '){
                read(p1[0], &f1, 1);
                input1[i] = f1;
                i++;
            }
            i--;
            input1[i] = '\0';
            int y;
            printf("Process B : Input value of y : ");
            fflush(stdin);
            scanf("%d", &y); 
            int inp1_int = atoi(input1);
            
            char buff2[100];
            sprintf(buff2, "%d ", inp1_int+y);
            write(p2[1], buff2, strlen(buff2));
            while(wait(NULL)>0){;}
            
        }
        else
        {
            char f1 = '$';
            char input1[50];
            int i=0;
            while(f1 != '\0' && f1 != '\n' && f1 != ' '){
                read(p2[0], &f1, 1);
                input1[i] = f1;
                i++;
            }
            i--;
            input1[i] = '\0';
            printf("Process C : Result after addition : %s\n", input1);
        }
    }
    else{
        int x;
        printf("Process A : Input value of x : ");
        fflush(stdin);
        scanf("%d", &x);
        char buff[50];
        sprintf(buff, "%d ", x);
        write(p1[1], buff, strlen(buff));
        while(wait(NULL)>0){;}
    }
    return 0;
}