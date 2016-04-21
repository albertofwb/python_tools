#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import subprocess
import time
import os
import sys

SLEEP_TIME = 10
services = {}
services['ssh_remote'] = ("unp_server.com", 35110, "/tmp/run.sh")

def scan_port(ip, port):
    try:
        socket.setdefaulttimeout(2)
        # default  family=2, type=1, proto=0
        s = socket.socket()
        s.connect((ip, port))
        s.close()
        return True
    except:
        return False


def check_service(config):
    host, port, exec_file = config
    if None in (host, port, exec_file):
        sys.exit(1)
    while True:
        if scan_port(host, port):
            os.system(exec_file)
            print "%s: %d is OnLine" %(host, port)
            print "I will be waiting for %d seconds" %SLEEP_TIME
        else:
            print "OFF"

        time.sleep(SLEEP_TIME)

if __name__ == '__main__':
     check_service (services['ssh_remote'])
