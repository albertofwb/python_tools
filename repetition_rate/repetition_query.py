#!/usr/bin/python

import os
import sys
import getopt
from get_src_list import get_src_list
from cmp_text import cmp_text

ARGS_LEN = 2
NO_CONFIG        = 0
CONFIG_FROM_CMD  = 1
CONFIG_FROM_FILE = 2
DEFAULT_TOP_DIR='/home'

def show_usage(proc_name):
    usage = '''\
                        Welcome to use Code repetition rate query
Desription:
    In case people copy source code from each other.

----------config-file-start-----------
TOP_DIR   /home                      |
USER_HOME                            |
{                                    |
    3130931001                       |
    3130931002                       |
}                                    |
COMPARING_FILES                      |
{                                    |
    /homework1/multi.c               |
}                                    |
----------config-file-end------------|
[Note]:
*    this config file is to guide the program run.
* each of `USER_HOME` and `COMPARING_FILES` should
* combine a legal path. No space allowed in the
* file_path.

|--------------------------------------|
|/home                                 |
|    ./3130931001      ./3130931002    |
|        ./homework1       ./homework1 |
|           multi.c          multi.c   |
|                                      |
|--------------------------------------|
[*]this program will compare:
    `/home/3130931001/homework1/src.c` and `/home/3130931002/homework1/src.c`

Usage_1: %s <top_dir_name>
Usage_2: %s [-F] [config-file]
Usage_2:  pre-edit a `config.ini` in the same path with this program.
'''%(proc_name, proc_name)
    print usage
    sys.exit(0)

def main(args):
    args_len = len(args)
    proc_name = args[0]
    run_level = NO_CONFIG
    top_dir   = ""
    src_list = []

    try:
        opts, args = getopt.getopt(sys.argv[1:], "h:d:F", ["help", "top-dir", "config-file"])
    except getopt.GetoptError as err:
        print str(err)
        show_usage(proc_name)

    for o, a in opts:
        if o in ("-h", "--help"):
            show_usage(proc_name)
        elif o in("-d", "--top-dir"):
            run_level = CONFIG_FROM_CMD
            top_dir = a
        elif o in("-f", "--config-file"):
            run_level = CONFIG_FROM_FILE
            config_file = a
        else:
            show_usage(proc_name)

    if run_level is NO_CONFIG:
        show_usage(proc_name)
    if run_level is CONFIG_FROM_CMD:
        src_list = get_src_list(run_level, top_dir)
    elif run_level is CONFIG_FROM_FILE:
        src_list = get_src_list(run_level, config_file)
    print "src_list:"
    for f in src_list:
        print f


if __name__ == '__main__':
    main(sys.argv)
