// Lisa Frye
// fork.c
// October 28, 2000
// Program to demonstrate the fork call

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
  pid_t pid;
  int *num = (int *)malloc(sizeof(int));
  int status;


  *num = 5;
  printf("PID: %d\tparent: %d\n\n", getpid(), getppid());

  // Create a child process
  switch (pid = fork()) {
  case -1:     // fork failed
    perror("fork");
    break;
  case 0:      // ??? process
    printf("In child, num = %d\n", *num);
    printf("process:   \t\tPID: %d\tparent: %d\n", getpid(), getppid());
    (*num)++;
    printf("In child, num = %d\n", *num);
    //sleep(200);  // test kill exit status
    exit(*num);

  default:
    printf("In parent, num = %d\n", *num);    
    printf("process after fork:   \tPID: %d\tparent: %d\n", getpid(), pid);
    *num=*num*3;
    printf("In parent, num = %d\n", *num);    

    int rv = wait(&status);
    if (rv == -1) {
      perror("Error in wait: ");
      exit(-1);
    }
    if (WIFEXITED(status))
      printf("PID %d exits: %d\n", pid, WEXITSTATUS(status));
    else if (WIFSTOPPED(status))
      printf("PID %d stopped by: %d\n", pid, WSTOPSIG(status));
    else if (WIFSIGNALED(status))
      printf("PID %d killed by: %d\n", pid, WTERMSIG(status));
    else
      printf("PID %d ended unknown status\n");

  }   // end switch


  printf("In parent, final num = %d\n", *num);    

  exit(0);
}  // end main

