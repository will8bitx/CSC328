#!/usr/bin/python
#***************************************************************
#* 
#* Author: Dr. Lisa Frye
#* Date: September 15, 2015
#* Filename: threads_helloWorld.py
#* Purpose: A simple Hello World program using threads
#*
#**************************************************************

import threading

# thread worker function
# Name: worker
# Arguments: num - an integer
# Return value: none
def worker(num):
    # print number passed to function
    print 'Worker: %s' % num
    return

threads = []   # array to hold each thread ID
# spawn 5 threads
for i in range(5):
    # create the thread
    t = threading.Thread(target=worker, args=(i,))
    threads.append(t)
    t.start()   # start the thread by calling run() method
