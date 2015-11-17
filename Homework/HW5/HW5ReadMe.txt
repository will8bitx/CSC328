***********************************/

This program was very interesting. I say that because I got it to work with a lot of research and asking questions. uthor: William Strouse Jr
* Date:  October 26th 2015
* HW5: Write a TCP client program for the Quote Of The Day (QOTD) protocol as
* defined by RFC 865. The hostname of the QOTD server should be passed as a
* command-line argument.
* Submit via turnin on acad (csit).

*Forgive me I'm longwinded, and I wanted to document what I had gone through
to make this progam work.
*
*Quote when I got it to work fully:
*Quote Of The Day: As long as there are ill-defined goals, bizarre bugs, and
unrealistic schedules, there will be Real Programmers willing to jump in and
Solve The Problem, saving the documentation for later.
***********************************/


I ran into 3 major issues: 
1) getting recv() to work correctly. My output was all what seemed to be memory addresses. What was tripping me up was the void *buf parameter. I thought I needed a pointer to match the declaration of the syntax based on the man pages. Online examples specified otherwise. 
 These kind of simple stumbling blocks seem to always trip me up and I start to panic and I don't see the real issue at hand, I get sidetracked going down the wrong detective path. At the advice of a classmate while experiencing other issues on the development of this program, he suggested 15 minutes on, then take a short break. After an hour I decided to take a break and then it hit me. I was using %d in my printf statement. Once I switched that to %s, the glorious QOTD server started returning quotes instead of numbers and our first milestone was completed. 
2) gethostbyname() - I heard horror stories in class about getting this to work correctly so I wanted to waste no time after the recv() was working. I was warned before the class started today regarding the segmentation faults and nothing I tried resolved the issue. Everytime I tried to use strcpy there was a warning regarding casting to const char * and I was at a loss. I then tried switching over to getaddrinfo() thinking, "Well this will be IVP6 ready anyway this will be better". Plus I found a great example to use as a guide. SAME ERROR. They both used a function in resolving the hostname to IP address "inet_ntoa()". Turns out this needs the <arpa/inet.h> include file. After this worked for the IPV6 I immediately uncommented all the code I had before and got that working. No more segmentation faults and we were getting the full quote of the day. 
3) MASSIVE ERRORS - after I wrote this I did one last oompile and BOOM.
everything blew up. Turns out there was an "i" at the very top of the file
that was throwing everything into chaos.  


Thanks,
-Will


