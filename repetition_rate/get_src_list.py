#!/usr/bin/python

import os

def get_src_list(top_dir):
    file_list = []
    pwd = os.getpwd()
    try:
        file_list = os.listdir(top_dir)
    except Exception as error:
        print error
    return file_list


