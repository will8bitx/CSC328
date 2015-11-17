/******************************************
* Author: William Strouse Jr
* Creation Date: October 21st 2015 - Back to the Future Day
* Due Date: October 21st 2015
* Course: CSC328 Network Programming
* Professor: Dr. Frye
* Assigment: HW4 - sockets timing
*******************************************/
HW4 - sockets timing

Used the gettimofday functionality to capture the difference in time between events. This requires the time.h header to be included. The call takes a struct and a deprecated timezone feature that we place NULL into per the man pages. I had a tough time finding an example of how to implement this, the man page does not include an example and I could see that a struct was needed, and this is where a lack of practice and working in code day in and day out works against me. I saw that the way the function worked was two private structs which held seconds and microseconds, allowing navigation through the order of magnitude by simple division/multiplication. I even worked on some code that would change the unit on the display based on the value of the difference, and then when that didn't work out took a look at the requirements again and saw that microseconds were essential.  

I was able to find an example that illustrated how to use gettimeofday, and from there I created two what I have called timers to hold the timestamp and calculate the difference in the output using the formula provided in the example. Example URL: //http://www.cs.loyola.edu/~jglenn/702/S2008/Projects/P3/time.html The 
 

Sample Output: 
[wstro208@csitrd HW4Update]$ ./tcpserv &
[1] 17481
[wstro208@csitrd HW4Update]$ Elapsed Socket allocation Time: 12 microseconds
Elapsed Bind Time: 7 microseconds
Elapsed Listen Time: 7 microseconds
Elapsed Socket Acceptance Time: 42688431 microseconds
Elapsed Connection Time: 127 microseconds
Elapsed Process Time: 0 microseconds
Elapsed Connection Time: 197 microseconds
Hello World!
Elapsed Socket Acceptance Time: 1653436 microseconds
Elapsed Connection Time: 132 microseconds
Elapsed Process Time: 0 microseconds
Elapsed Connection Time: 208 microseconds
Hello World!
Elapsed Socket Acceptance Time: 841569 microseconds
Elapsed Connection Time: 123 microseconds
Elapsed Process Time: 1 microseconds
Elapsed Connection Time: 195 microseconds
Hello World!
Elapsed Socket Acceptance Time: 801785 microseconds
Elapsed Connection Time: 156 microseconds
Elapsed Process Time: 1 microseconds
Elapsed Connection Time: 233 microseconds
Hello World!
Elapsed Socket Acceptance Time: 743690 microseconds
Elapsed Connection Time: 117 microseconds
Elapsed Process Time: 0 microseconds
Elapsed Connection Time: 205 microseconds
Hello World!


Analysis:

Why do some calls require orders of magnitude more time than others?

So what I was able to see from running this from csit to hermione and vice versa is that consistently the largest consumption of time was when the socket descriptor was set to the transport end point. The question is why. First, this measurement takes into account the time between calls from the client. As I've been typing up this readme I've just re-run the client to demonstrate:
 
[wstro208@csitrd HW4Update]$ Elapsed Socket Acceptance Time: 1266171913 microseconds

Additionally the operations in the operating system that take the longest time are disk I/O. Here we are setting a socket descriptor to a socket declaration which is setting up a TCP connection via SOCK_STREAM. I suddenly wonder if this would be faster with UDP. My hypothesis is that it would be faster than TCP but not the levels of magnitude faster since we are basically creating an I/O operation with socket descriptors. 


