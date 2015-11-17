/*****************************************************************************
 * Author: William Strouse Jr
 * Creation Date: September 21st 2015
 * Due Date: September 21st 2015
 * Course: CSC328 Network Programming
 * Professor Name: Dr. Frye
 * Assignment: HW3
 * Filename: childTest_WS.c
 * Purpose: This program will create 5 child processes from a single
 * program and display text to the screen from each process.
 * Functionality has been extended to apply a Ceaser Cipher to the
 * text shifting the characters displayed. The processID is 
 * shown executing.
 *
 * Compiler instructions: gcc -o childTest_WS childTest_WS.c -lpthread
****************************************************************************/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{

//grab the pid
pid_t processID;
//int x = 100;
//printf("#BlameWill before the fork");
char string1[33] = "BE SURE TO DRINK YOUR OVALTINE";
char string2[375] = "In 1972, a crack commando unit was sent to prison by a military court for a crime they didn't commit. These men promptly escaped from a maximum security stockade to the Los Angeles underground. Today, still wanted by the government they survive as soldiers of fortune. If you have a problem, if no one else can help, and if you can find them....maybe you can hire The A-Team.";
//create the child process
/*
for(int i; i<5; i++)
{
 processID = fork();
}
*/
/*
switch (processID = fork())
{
	case -1: //failure of fork
		perror("#BlameWill - fork failure");
		break;
	case 0: //inside child
		x++;
		printf("After fork within child: shoottheJ = %d\n", x);
		break;
	default:
		sleep(1);
		printf("After fork Parent #BlameWill: shoottheJ = %d\n", x);
}//end switch
*/

//need to build a loop that forks
//need to build a fork that is testing for child process THEN loops
processID = fork(); 
if (processID == 0) //child process
{

	char cipherText[375];
//	ptid_t childID = getpid();
	//cipherText = string1; //throws error need char * - will need to research
	int i, x;
	for (x=0; x<5; x++)
	{
		for(i=0; i<strlen(string2); i++)
		{		
		//	processID = fork(); //THIS CAUSES INFINITE LOOPING
		//printf("string1: %s\n", string1);
		//account for spaces in the cipher
		//printf("string1: %s\n", string1[i]);
			if (string2[i] == ' ')
			{
			cipherText[i] = ' ';//string1[i];
		//	printf("space detected: %c\n", cipherText[i]); //I would expect the cipherText[i] to be equal to a space;
			}
		//account for Z as a wraparound character to A
			if (string2[i]+x == 'Z')
			{cipherText[i] = 'A';}
			else if(string2[i] != ' ')
			{
			 if(x==0)
			 {cipherText[i] = string2[i]+x+26;} //special processing for 0 
			else if(x>0)
			 {cipherText[i] = string2[i]+x;}
			 
			} //copy each character to the cipherText - will need to do this pre-for loop for iterative cipher
			//printf("string1[i]: %c\n", string1[i]); 
		}//end cipher for
	printf("\n\nProcessID: %d cipherText: %s\n", getpid(), cipherText);
	} //end 5 loop for
	//printf("\ncipherText %s\n", cipherText);
	return 0;

}//end if
if (processID > 0) //parent process
{
	wait(); //wait for child to end
} 
else//error
{
	printf("#BlameWill for the error received here\n");
	printf("ProcessID: %d\n", processID);
}


return 0;
}//end main
