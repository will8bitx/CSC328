// Lisa Frye
// forkOutput.c
// March 2009
// Program to demonstrate the fork call 

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
  pid_t pid;
  int j = 200; 


  printf("before fork call: j = %d\n", j);


  // Create a child process
  switch (pid = fork()) {
    case -1:     // fork failed
      perror("fork");
      break;
    case 0:      // child process
      j++;
      printf("After fork call, child: j = %d\n", j);
      break;
    default:
      sleep(1);
      printf("After fork call, parent: j = %d\n", j);
  }   // end switch


  return 0;
}  // end main

