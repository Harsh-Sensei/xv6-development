#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <fcntl.h> 

using namespace std;



int main(int argc, char* argv[])
{   

    char file1[50], file2[50];
    char f1 = '$', f2 = '$';
    int i = 0;
	char buf;
    while(f1 != '\0' && f1 != '\n' && f1 != ' '){
        read(STDIN_FILENO, &f1, 1);
        file1[i] = f1;
        i++;
    }
    i--;
    file1[i] = '\0';
    
    i = 0;
    while(f2 != '\0' && f2 != '\n' && f2 != ' '){
        read(STDIN_FILENO, &f2, 1);
        file2[i] = f2;
        i++;
    }
    i--;
    file2[i] = '\0';

    int fd1, fd2;

	fd1 = open(file1, O_RDONLY);

	if (fd1 == -1)
	{
		close(fd1);
		return 1;
	}

	fd2 = open(file2, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	
	while(read(fd1, &buf, 1))
	{
		write(fd2, &buf, 1);
	}
    
    return 0;
}