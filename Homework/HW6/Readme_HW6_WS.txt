/******************************************
* Author: William Strouse Jr
* Creation Date: November 2nd 2015
* Due Date: November 2nd 2015
* Course: CSC328 Network Programming
* Professor: Dr. Frye
* Assigment: HW6 - Library Creation
*******************************************/
I was unable to compile the sockutils.c using the -fpic flag without using the -c flag as well. 
This is due to the fact the -c flag does not link the library, and the following library was throwing an error: 
/usr/lib/gcc/x86_64-redhat-linux/4.4.7/../../../../lib64/crt1.o: In function `_start':
(.text+0x20): undefined reference to `main'
collect2: ld returned 1 exit status

With the -c flag used, the library isn't attempted to be linked, and the error is not thrown. 

I wanted to note that in the script file there are backspaces marked by the following character: [K

Additionally I have the file incorrectly marked as HW5_WS when this is actually HW6. I have since corrected the directory. 

Thanks,
-Will Strouse Jr. 
