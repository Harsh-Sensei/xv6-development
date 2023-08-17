#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

// TODO: YOUR CODE HERE
// INITIALIZE DATA STRUCTURE TO STORE PIDS OF PROCESSES TO KILL LATER

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line) {

    // tokenizer variables
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

    // loop on length of line
	for(i=0; i < strlen(line); i++){

		char readChar = line[i];

        // tokenize on any kind of space
		if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
			token[tokenIndex] = '\0';
			if (tokenIndex != 0) {
				tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0; 
			}
		}
		else {
			token[tokenIndex++] = readChar;
		}
	}
	
	free(token);
	tokens[tokenNo] = NULL ;
	return tokens;
}

// TODO
// MAKE FUNCTIONS AS REQUIRED TO AVOID REPETITIVE WORK

int main(int argc, char* argv[]) {

	char  line[MAX_INPUT_SIZE];            
	char  **tokens;           

	// TODO: YOUR CODE HERE
	// INITIALIZE GLOBAL DATA STRUCTURE OF PIDS TO SOME DEFAULT VALUE  
	// INITIALIZE OTHER VARIABLES AS NEEDED

	while(1) {	

		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);	
		
		
		// You can maintain boolean variables to check which type of command is given by user and then
        // conditionally execute depending on them
		int idx = 0;
		
		int num_tokens = 0;
		int pid_array[MAX_NUM_TOKENS] = {0};

		bool two_arg_stage1 = false;
		bool two_arg_stage2 = false;
		bool one_arg = false;

		bool finished_command = false;

		char buff1[MAX_TOKEN_SIZE];
		char buff2[MAX_TOKEN_SIZE];
		char cmd[MAX_TOKEN_SIZE];
		char dir[] = "/usr/bin/";

		bool chgdir = false;
		
		char *args[MAX_NUM_TOKENS] = {NULL};

		while(tokens[idx] != NULL)
		{	
			if(two_arg_stage1)
			{
				two_arg_stage1 = false;
				two_arg_stage2 = true;
				sprintf(buff1, "%s", tokens[idx]);
				idx++;
				continue;
			}
			if(two_arg_stage2)
			{
				sprintf(buff2, "%s", tokens[idx]);
				finished_command = true;
			}

			if(one_arg)
			{
				sprintf(buff1, "%s", tokens[idx]);
				finished_command = true;
			}
			if(chgdir)
			{
				chdir(tokens[idx]);
				idx++;
				continue;
			}

			if(!finished_command)
			{
				if(strcmp(tokens[idx], "&&") == 0)
				{
					wait(NULL);
					idx++;
					continue;
				}

				if(strcmp(tokens[idx], "&&&") == 0)
				{
					idx++;
					continue;
				}
				if(strcmp(tokens[idx], "diff") == 0 || strcmp(tokens[idx], "kill") == 0)
				{	
					sprintf(cmd, "%s%s", dir, tokens[idx]);
					two_arg_stage1 = true;
					idx++;
					continue;
				}
				if(strcmp(tokens[idx], "cat") == 0 || strcmp(tokens[idx], "echo") == 0 || strcmp(tokens[idx], "sleep") == 0)
				{
					sprintf(cmd, "%s%s", dir, tokens[idx]);
					one_arg = true;
					idx++;
					continue;
				}

				if(strcmp(tokens[idx], "man") == 0 || strcmp(tokens[idx], "touch") == 0 || strcmp(tokens[idx], "mkdir") == 0)
				{	
					sprintf(cmd, "%s%s", dir, tokens[idx]);
					one_arg = true;
					idx++;
					continue;
				}
				if(strcmp(tokens[idx], "rm") == 0 || strcmp(tokens[idx], "rmdir") == 0)
				{
					sprintf(cmd, "%s%s", dir, tokens[idx]);
					one_arg = true;
					idx++;
					continue;
				}
				if(strcmp(tokens[idx], "cd") == 0)
				{
					chgdir = true;
					continue;
				}
			}
			

			if(strcmp(tokens[idx], "ls") == 0 || strcmp(tokens[idx], "clear") == 0 || strcmp(tokens[idx], "pwd") == 0 || strcmp(tokens[idx], "ps") == 0)
			{
				sprintf(cmd, "%s", tokens[idx]);
			}
			finished_command = false;

			if(two_arg_stage2)
			{
				two_arg_stage2 = false;
				args[0] = cmd;
				args[1] = buff1;
				args[2] = buff2;

			}
			else if(one_arg)
			{
				one_arg = false;
				args[0] = cmd;
				args[1] = buff1;
			}
			else
			{
				args[0] = cmd;
			}

			if(fork() == 0)
			{	
				execvp(args[0], args);
			}
			idx++;
		}

		while(wait(NULL)>0)
		{
			;
		
		}

        // TODO: YOUR CODE HERE
        //
        // TODO: YOUR CODE HERE
    
        // freeing the memory
		for(int i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}

		free(tokens);

	}
	return 0;
}


