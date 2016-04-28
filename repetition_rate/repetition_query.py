#!/usr/bin/python

import sys

ARGS_LEN = 2

def show_usage(proc_name):
    usage = '''       Welcome to use this program.
    %s filenames\n" %(proc_name)
'''
    return usage

def main(args):
    args_len = len(args)
    proc_name = args[0]

    if args_len < ARGS_LEN:
        print show_usage(proc_name)
    else:
        print "Running"

if __name__ == '__main__':
    main(sys.argv)
