#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    int fd[2];
    pipe(fd);
    char *cmd;
    char readbuffer[20];
    
    
    pid_t process;
    
    if((process = fork()) == 0) //child process
    {
        printf("child process pid: %d\n",getpid());
        close(fd[1]); 
        read(fd[0], readbuffer, sizeof(readbuffer));
	cmd=&readbuffer[5];
   	if(strcmp("echo",cmd)==0)
        {
                execl(readbuffer,cmd,"Hello world",0);
        }
        else
        {
                execl(readbuffer,cmd,0,0);
        }
	exit(0);
    }
        
    else if(process > 1)   //parent process
    {
        close(fd[0]);
        printf("parent process pid: %d\n",getpid());
        write(fd[1], argv[1], (strlen(argv[1])+1));
	wait(&process);
    }

    else
    {
	perror("No new process is created");
    }
	return 0;
}

