#!/usr/bin/python

import os
import sys
import getopt
from config import config_set 
from cmp_text import cmp_text

DEFAULT_TOP_DIR='/home'

def show_usage(proc_name):
    usage = '''\
Desription:
    In case people copy source code from each other.

Usage: %s <-d> <top_dir_name>
'''%(proc_name)
    print usage
    sys.exit(0)

def get_src_list(top_dir):
    file_list = []
    pwd = os.getcwd()
    try:
        file_list = os.listdir(top_dir)
    except Exception as error:
        print error
    return file_list


def main(args):
    proc_name = args[0]
    opt       = args[1]
    config_file = ""
    top_dir     = ""
    src_list = []

    if opt in ("-h", "--help"):
        show_usage(proc_name)
    elif opt in("-d", "--top-dir"):
        print get_src_list(args[2])
    else:
        print config_set

if __name__ == '__main__':
    main(sys.argv)
