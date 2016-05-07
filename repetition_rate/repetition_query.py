#!/usr/bin/python

import os
import sys
from config import init_mem

def show_usage(proc_name):
    usage = '''\
Desription:
    In case people copy source code from each other.

Usage: %s <-d> <top_dir_name>
'''%(proc_name)
    print usage
    sys.exit(0)

def cmp_func(users):
    this_user = 0
    users_total = len(users)

    while this_user < users_total:
        cmp_user = this_user + 1
        while cmp_user < users_total:
            src_tag = users[this_user].get_md5(cmp_file)
            tar_tag = users[cmp_user].get_md5(cmp_file)
            if not cmp(users[this_user].get_md5(cmp_file), users[cmp_user].get_md5(cmp_file)):
                users[this_user].set_equal_flag(users[cmp_user].get_account())
                users[cmp_user].set_equal_flag(users[this_user].get_account())



def main():
    users = init_mem()
    cmp_func(users)

    users_total = len(users)
    print ("total users: %d") %(users_total)
    for u in users:
        print u

if __name__ == '__main__':
    main()
