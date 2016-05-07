#! /usr/bin/python

import os
import re
import hashlib

user_name_file = "users.txt"
#top_dir = "/home"
top_dir = "/home/albert/git/Python/repetition_rate/data/"
user_format = "\d{10}"
homework_list = ["homework1/str_echo.c", "homework2/dns.c"]

def get_homeworks():
    return homework_list

def filter_buffer(buff):
    buff_len = len(buff)
    new_buff = ''
    loop = 0
    while loop < buff_len:
        ch = buff[loop]
        if ch.isspace() or ch.isdigit():
            loop += 1
            continue
        else:
            new_buff += ch
        loop += 1
    #print new_buff
    return new_buff

class User():
    def __init__(self, num, name, path_list):
        self.name       = name
        self.account    = num
        self.files      = path_list
        self.files_buff = []
        self.files_hash = {}
        self.copied_whom= []
        #self.what_copied= []
        self.check_time = 0

    def get_md5(self, path):
        path = os.path.join(top_dir, self.account, path)
        return self.files_hash[path]

    def get_account(self):
        return self.account

    def is_checked(self):
        return self.check_time

    def set_check(self):
        self.check_time += 1

    def set_equal_flag(self, user, filename):
        self.copied_whom.append((user, filename))

    def have_file(self, path):
        files = ' '.join(self.files)
        #print "%s in %s %d" %(path, files, path in files)
        return path in files

    def is_copy(self):
        ret = self.account
        if self.check_time:
            ret += ' copied'
            for i in self.copied_whom:
                ret = ret + ' *' + i[0] + '* [' + i[1] +']'
            return ret

    def read_files(self):
        for path in self.files:
            with open(path) as fp:
                self.files_buff.append([path, fp.read()])

    def hash_files(self):
        for path, buff in self.files_buff:
            md5 = hashlib.md5(filter_buffer(buff)).hexdigest()
            self.files_hash[path] = md5

    def __str__(self):
        ret = '''\
account: %s
name:    %s
files:   %s''' %(self.account, self.name, '\n'.join(self.files))
        return ret

def get_active_dir():
    fmt = re.compile(user_format)
    active_users = os.listdir(top_dir)
    active_users = ' '.join(active_users)
    active_users = fmt.findall(active_users)
    return active_users

def map_name():
    users_dict = {}
    fp = open(user_name_file)

    for line in fp:
        line = line.strip().split()
        if len(line) > 2:
            account, name = line[0:2]
            users_dict[account] = name
    return users_dict




def init_mem():
    active_users = get_active_dir()
    users_dict   = map_name()
    user_list = []
    for i, account in enumerate(active_users):
        name = users_dict.get(account)
        path_list = []

        for path in homework_list:
            cur_path = os.path.join(top_dir, account, path)
            if os.path.isfile(cur_path):
                path_list.append(cur_path)
        #print name, path_list
        user_info = User(account, name, path_list)
        user_info.read_files()
        user_info.hash_files()
        user_list.append(user_info)

    return user_list

def debug():
    users = init_mem()
    for u in users:
        print u.name
        print u.files_hash

if __name__ == '__main__':
    debug()
