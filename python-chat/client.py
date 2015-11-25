#! /usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 24 17:35:50 2013
 
@author: zbg
"""
 
import socket
import threading
from config import *
 
 
inString = ''
outString = ''
nick = ''
 
def DealOut(s):
    global nick, outString
    while True:
        outString = raw_input()
        outString = nick + ': ' + outString
        s.send(outString)
 
def DealIn(s):
    global inString
    while True:
        try:
            inString = s.recv(1024)
            if not inString:
                break
            if outString != inString:
                print inString
        except:
            break
         
 
nick = raw_input("input your nickname: ")
ip = raw_input("input the server's ip adrress: ")
if len(ip) < 1:
    ip = DEFAULT_IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((ip, 8888))
sock.send(nick)
 
thin = threading.Thread(target = DealIn, args = (sock,))
thin.start()
thout = threading.Thread(target = DealOut, args = (sock,))
thout.start()
 
#sock.close()
