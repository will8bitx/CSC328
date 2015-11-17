// forkexecwait.c
// October 28, 2000
// Program to illustrate fork, exec, and wait system calls

#include <sys/types.h>
#include <unistd.h>


int main()
{
  pid_t pid;
  char *args[4];

  // Create a child process
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(-1);
  }  // end if


  if (pid == 0) {
    // Code executed by child process
    execl("/bin/echo", "echo", "Today's", "date", "is:", NULL);

    // if exec succeeds this code will not execute
    perror("Child exec did not succeed: ");
    exit(-1);
  }  // end if

  // code for parent process to execute
  args[0] = "date";
  args[1] = "+%A, %B %d, %Y";
  args[2] = NULL;

  execv("/bin/date", args);

  // if exec succeeds this code will not execute
  printf("Parent exec did not succeed!!\n");
  perror("exec");
  exit(-1);
}  // end main
