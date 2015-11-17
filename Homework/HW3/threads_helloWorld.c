/******************************************************************************
 *
 * Author: Dr. Lisa Frye
 * Creation Date: August 28, 2015
 * Filename: hello.c
 * Purpose: A Hello World program to illustrate pthreads.
 * Compile:  gcc helloWorld.c -lpthread
 *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>   // for exit()
#include <pthread.h>  // for pthread functions

#define NUM_THREADS	5

void *print(void *threadid);


int main(int argc, char *argv[])
{
  int i, rc;
  pthread_t threads[NUM_THREADS];
 
  for(i=0; i < NUM_THREADS; i++){
     printf("Creating thread %d\n", i);

     // create a thread and call the print function
     // store ID of new thread in threads array
     // i is passed as the argument to the print function
     rc = pthread_create(&threads[i], NULL, print, (void *)i);

     if (rc){  // if error creating thread
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
     } // end if
  }  // end for

  pthread_exit(NULL);
}  // end function main


/**************************************************************
 *
 * Function name: print
 * Description: print "Hello World"
 * Parameters: threadid - the ID of the current thread
 * Return Value: none
 *
 **************************************************************/
void *print(void *threadid)
{
   printf("\n%d: Hello World!\n", threadid);

   // terminate the calling hread
   pthread_exit(NULL);
}   // end function print
