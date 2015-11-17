/*************************************
 *
 *
 *
 *
 * ***********************************/

//includes
#include <sys/types.h>
#include <stdio.h>

int main()
{

//grab the pid
pid_t processID;
int x = 8; 
printf("#BlameWill before the fork");

//create the child process
/*my approach is wrong, will create an infinite loop
for(int i; i<5; i++)
{
 processID = fork();
}
*/

switch (pid = fork())
{
case -1: //failed fork
 perror("#BlameWill Fork:");
 break;
case 0: //child process
x++;
printf("After fork call, child will #BlameWill: x = %d\n", x);
break;
default:
sleep(1);
printf("After fork PARENT x = %d\n", x);
}//end switch


return 0;
}//end main
