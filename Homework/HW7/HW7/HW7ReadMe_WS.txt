/**********************************************************
 * Author: William Strouse Jr
 * Creation Date: November 9th 2015
 * Modified Date: November 10th 2015
 * Due Date: November 9th 2013
 * Course: CSC 328
 * Professor Name: Dr. Lisa Frye
 * Assigment: HW7
 * Filename: server.c client.c
 * Purpose: Write an iterative, connectionless server for the client program sockets/UDP in the course’s public directory on the acad system.
 * Turn in the server code using turnin on acad.
***********************************************************/
FUNCTIONALITY: 
When using the UDP Server, it will take any text passed from the client and convert the a-z values to uppercase. Any uppercase letters will be returned to the client as is, as well as digits and other non-alpha characters. 

PORT USED: 50018

TESTING: 
Of all the key combinations tested, only CTRL+4 produced a crash. Please avoid (or test) this key combination while passing values to this server. ALT+ASCII values work: ® = ALT+0174.

ERROR HANDLING: 
I used perror around the socket operations, and I set the size of the buffer to the size of the client we're receiving in. Preliminary tests went well with only one instance copied from the web where the text was showing mixed case. This may have been due to html characters being passed in. 

DEVELOPMENTAL NOTES: 
Ran into a huge roadblock while developing this solution. The problem was I failed to set the values of the server after the memory was cleared by memset. I had issues with the toupper when I was trying to do that on the fly in the sendto() call, and that was having a fit. Since the toupper returns an int value and in the sendto it's looking for a const char *. Casting seemed impossible so I ended up creating a safe way for future expansion on the idea and assigned the buf to itself after running the toupper. I tested with a second char array at first and then tried setting buf to itself and it worked beautifully. 


