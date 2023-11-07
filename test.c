#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[], char *envp[]) {
    
    pid_t pid =0 ;
    int		status = 0;

    char *args[] = {"/usr/bin/gedit", "", NULL};
    
    pid  = fork();
    if (pid < 0)
    {
        perror("Something wrong");

    }else if(pid > 0){
        waitpid(pid, &status, 0);
		kill(pid, SIGTERM);

    }else
    {
            execve(args[0], args, envp);
            perror("execve");
    }
    
    return 1;
}