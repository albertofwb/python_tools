#! /usr/bin/python

import os
import re

user_name_file = "users.txt"
top_dir = "/home"
user_format = "\d{10}"
homework_list = ["homework1/multi.c", "homework2/dns.c"]
users_dict = {}
active_users = []
user_list = []


class User():
    def __init__(self, num, name, path_list):
        self.name = name
        self.numb = num
        self.files= path_list

    def my_name(self):
        return self.name

    def my_files(self):
        return self.files

    def get_no_src(self, no=0):
        return self.files[no]

    def get_src_count(self):
        return len(self.files)

    def __str__(self):
        return self.name

def get_active_dir():
    fmt = re.compile(user_format)
    active_users = os.listdir(top_dir)
    active_users = ' '.join(active_users)
    active_users = fmt.findall(active_users)

def read_user_name():
    fp = open(user_name_file)

    for line in fp:
        line = line.strip()
        if len(line) > 1:
            line = line.split()
            users_dict[line[0]] = line[1]




def init_mem():
    print active_users
    for i, user in enumerate(active_users):
        print i
        user_list[i] = User(users[i], users_dict[users[i]], [os.path.join(top_dir, users[i], path) for path in homework_list])

read_user_name()
get_active_dir()
init_mem()

print len(user_list)
