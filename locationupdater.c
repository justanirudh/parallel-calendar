#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1
/*
dup(oldfd)
dup2(oldfd, newfd)
The dup() system call creates a copy of the file descriptor oldfd,
       using the lowest-numbered unused file descriptor for the new
       descriptor
The dup2() system call performs the same task as dup(), but instead
       of using the lowest-numbered unused file descriptor, it uses the file
       descriptor number specified in newfd.  If the file descriptor newfd
       was previously open, it is silently closed before being reused.*/
int main(int argc, char* argv[]) 
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid==0) //child, email_filter
    {
				close(fd[READ_END]); //closing read end of pipe
        dup2(fd[WRITE_END], STDOUT_FILENO); //creates copy of fd's write end as the file's stdout (overwrites stdout's previous functionality)
				close(fd[WRITE_END]);//descriptor no longer reqd as already duped
				execlp("./emailfilter", "emailfilter", NULL);

		}
    else //parent, calendar_filter
    { 
			close(fd[WRITE_END]);//closing write end of pipe
			dup2(fd[READ_END], STDIN_FILENO);//redirecting stdin of file to fd[0], read end of pipe
			close(fd[READ_END]); //descriptor not reqd as already duped
			execlp("./calenderfilter", "calenderfilter", NULL);
		}

    return 0;
}
