#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>



int main()
{
	omp_set_dynamic(0);
	
	#pragma omp parallel num_threads(4)
	{
		int currentThread = omp_get_thread_num();
		if(currentThread == 0)
		{
			printf("Master!\n");
			int i = 0;
			while(i < 100000)
			{
				i++;
			}
			printf("Master Completed!\n");
		}
		else
		{
			printf("Slave!\n");
			int pid = fork();
			if(pid == 0)
			{
				char* args[2];
				args[0] = "test2";
				args[1] = NULL;
				if(execvp("./test2",args) == -1)
				{
					fprintf(stderr, "ERROR: failed to run execvp\n");
				}
				exit(-1);
			}
			else
			{
				while(1)
				{
					int status;
					int id = waitpid(pid,&status, WNOHANG | WUNTRACED);
					if(id == -1)
					{
						//exit(EXIT_FAILURE);
						printf("Exiting...\n");
		      				exit(-1);
					}
					else if(id == 0) // child still running
					{
						
					}
					else if(WIFEXITED(status))
					{
						printf("Terminated normally\n");
						break;
					}
					else if(WIFSIGNALED(status))
					{
						printf("Unexpected error\n");
						exit(-2);
					}
				}
			}
		}
	}
	return 0;
}
