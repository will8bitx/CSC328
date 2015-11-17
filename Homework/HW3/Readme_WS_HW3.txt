/***********************************************************************
* Author: William Strouse Jr
* Creation Date: September 21st 2015
* Due Date: September 21st 2015
* Course: CSC328 Network Programming
* Professor Name: Dr. Frye
* Assignment: HW3
* ***********************************************************************/

1. Process Program

Write a concurrent program that starts five processes. The main thread in each process should print a few lines of output and then halt. Have the output be a favorite or famous saying or quote.

I have completed this under the childTest_WS.c program. 

Approach: I went with if statements to handle the process ID management, and did some simple error handling for values of processID that were not either 0 (child) or greater than 0 (parent). 

I was trying many different approaches at first and ended up with
a Cesear Cipher program after going through a Khan academy course on 
cryptography. 

Issues/Difficulty: Compiler warnings regarding strlen, but the program still works as expected. After programming threads I had to go back and change the quote, and how the iterative loop was handling the 0 value, since there was no shift. Another issue was getting the values to "wrap" around after Z. Simple 135 mistake of using = rather than ==. 


2. Thread Program

Write a program that creates five concurrent threads within a single process. Each thread should print a few lines of output and then halt. Have the output be a favorite or famous saying or quote.


The thread program was completed under the threadTest_WS.c

Approach: Once I figured out that you could pass values to threads, and when you cleared up what values we could/should pass for this exercise that set me on my way. The approach was to pass in the threadID and have that be the constant that shifted the cipher. 

Issues/Difficulty: Wrapping my mind around the initial thread_create and the pointers was really throwing me. I did more research into pointers in C & threads to get over this barrier. 
I tried to randomize this, but rand() is not thread safe! I couldn't figure out what was going on and I was getting the same values for each thread, and I figured the time increment was so fast it didn't generate a unique seed. After pouring through the man pages, it said that it saves information in the state and the seeds were one of them. This explained my 5 values all the same. I could have used drand48_r but I ran out of implementation time.

 
MISC: Looking at these side by side I did not account for spaces like I did with the process child. 

/****************************************************************
3. Program Comparison

Compare the running time of the process program with the running time of the thread program. Write an expression for the difference in cost as a function of three parameters: the size of global variables, the size of local variables, and the execution time of the threads.
****************************************************************/

Execution: I used /usr/bin/time -v to measure the execution of these programs. Now let me preface this by saying they were both done in 0.02ms. That being said the threads optimized CPU usage over processes. This was illustrated by the statistic: Percent of CPU this job got: 50% was a consistent factor when running the thread version. The only memory statistic I could see was higher, surprisingly, for the threads as well:  Minor (reclaiming a frame) page faults. This could mean higher impact to memory resources. 

Implementation: After programming threads I can say that processes are much easier to implement. 

Bottom Line: What this comes down to is the requirements. If the client/target of the program you are designing needs speed and they have the supporting infrastructure in place, threads seem like a great way to take advantage of multiple core processors. The tradeoff is development and implementation time would be longer. We have to build reliable, complete solutions from top to bottom and most of the time this means finding out what the clients actual needs are and asking the tough questions up front. If we can find out that the hardware budget doesn't allow for upgrades in the next 5 - 10 years since the system you are helping implement is their big bugetary spend, then that will change your perspective. 
I once interviewed at a hospital and they said, "We have what we have, and we have to make the most of what is here, there is no room for upgrades." This situation calls for reliability and maximizing the aging systems in place, and could mean performance can take a hit for stability, especially in a healthcare setting. 

In the end getting to know the actual users of the system, building use cases, testing side by side are things that rarely happen. Designing with the end in mind will teach that the right answer is determined by a number of factors out of your control unfortunately. Having the knowledge to being able to adapt to these scenarios and create solutions that work is our greatest strength when asked to do the impossible. 

Side note: 
I wanted to eventually try to brute force the creation and test
threads vs processs, I have a feeling that the threads would really get to the solution faster. 
