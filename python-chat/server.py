#! /usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri Oct 25 10:33:44 2013
 
@author: zbg
"""
from config import *
import socket
import sys
import threading
 
con = threading.Condition()
HOST = raw_input("input the server's ip adrress: ") # Symbolic name meaning all available interfaces
if len(HOST) < 1:
    HOST = DEFAULT_IP

PORT = 8888 # Arbitrary non-privileged port
data = ''
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
print 'Socket created'
s.bind((HOST, PORT))
s.listen(10)
print 'Socket now listening'
 
#Function for handling connections. This will be used to create threads
def clientThreadIn(conn, nick):
    global data
#infinite loop so that function do not terminate and thread do not end.
    while True:
    #Receiving from client
        try:
            temp = conn.recv(1024)
            if not temp:
                conn.close()
                return
            NotifyAll(temp)
            print data
        except:
            NotifyAll(nick + " leaves the room!")
            print data
            return
 
    #came out of loop
 
def NotifyAll(sss):
    global data
    if con.acquire():
        data = sss
        con.notifyAll()
        con.release()
  
def ClientThreadOut(conn, nick):
    global data
    while True:
        if con.acquire():
            con.wait()
            if data:
                try:
                    conn.send(data)
                    con.release()
                except:
                    con.release()
                    return
                     
 
while 1:
    #wait to accept a connection - blocking call
    conn, addr = s.accept()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])
    nick = conn.recv(1024)
    #send only takes string
    #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
    NotifyAll('Welcome ' + nick + ' to the room!')
    print data
    print str((threading.activeCount() + 1) / 2) + ' person(s)!'
    conn.send(data)
    threading.Thread(target = clientThreadIn , args = (conn, nick)).start()
    threading.Thread(target = ClientThreadOut, args = (conn, nick)).start()
 
s.close()
