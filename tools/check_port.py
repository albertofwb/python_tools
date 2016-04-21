#!/usr/bin/python
# -*- coding: utf-8 -*-
import socket
import subprocess
import time
import os
import sys

SLEEP_TIME = 5
LOG_FILE = '/tmp/remote_ssh.log'
services = {}
services['ssh_remote'] = ("unp_server.com", 35110, "~/bin/enable_remote_ssh")

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

def is_connect2net():
    return scan_port("www.baidu.com", 80)

def check_service(config, verbose):
    host, port, exec_file = config
    check_counter = 0
    status = ["OFFLINE", "ONLINE"]
    information = ""
    fp = open(LOG_FILE, 'a+')
    if None in (host, port, exec_file):
        sys.exit(1)

    host_info = "[%s:%d]" %(host, port)
    while True:
        ret = scan_port(host, port)
        information = "%d %s %s sleeping for %d seconds\n" %(check_counter, host_info, status[ret], SLEEP_TIME)
        if ret is True:
            pass
        else:
            if is_connect2net():
                os.system(exec_file)
            else:
                information = "failed to connect to internet\n"

        check_counter += 1

        cur_time = time.strftime('[%Y-%m-%d %H:%M:%S] ')
        information = cur_time + information
        if not verbose:
            fp.write(information)
            fp.flush()
        else:
            print information.strip()
        time.sleep(SLEEP_TIME)

if __name__ == '__main__':
    verbose = False
    args = ""
    if len(sys.argv) == 2:
        args = sys.argv[1]
    if args.lower() == 'show':
        verbose = True

    check_service (services['ssh_remote'], verbose)
