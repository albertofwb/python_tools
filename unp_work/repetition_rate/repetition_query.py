#!/usr/bin/python

import os
import sys
from config import init_mem, get_homeworks

def show_usage(proc_name):
    usage = '''\
Desription:
    In case people copy source code from each other.

Usage: %s <-d> <top_dir_name>
'''%(proc_name)
    print usage
    sys.exit(0)

def cmp_func(users, cmp_file):
    this_user = 0
    users_total = len(users)

    #print "users_total: %d" %(users_total)
    while this_user < users_total:
        cmp_user = this_user + 1
        while cmp_user < users_total:
            #print "checking exist: ", cmp_file
            this = users[this_user]
            other = users[cmp_user]
            if this.have_file(cmp_file) and other.have_file(cmp_file):
                source = this.get_md5(cmp_file)
                target = other.get_md5(cmp_file)
                if not cmp(source, target):
                    this.set_check()
                    this.set_equal_flag(other.get_account(), cmp_file)
                    other.set_equal_flag(this.get_account(), cmp_file)
            cmp_user += 1
        this_user += 1



def main():
    users = init_mem()
    homeworks = get_homeworks()
    for work in homeworks:
        cmp_func(users, work)

    for u in users:
        if u.is_checked():
            print u.is_copy()

if __name__ == '__main__':
    main()
