#! /usr/bin/python
#encoding: utf-8

import os, sys

path = '/tmp'

def enumerate_paths(path = path):
    # Returns the path to all the files in a directory  recursively.
    path_collection = []
    for dir_path, dir_names, file_names, in os.walk(path):
        path_collection = [os.path.join(dir_path, single_file) for single_file in file_names]

    return path_collection

def enumerate_files(path = path):
    # Return all the files in a directory as a list
    file_collection = []
    for dir_path, dir_names, file_names in os.walk(path):
        file_collection.extend(dir_names)

    return file_collection

def enumerate_dir(path = path):
    # Return all the directories in a directory as a list
    dir_collection = []
    for dir_path, dir_names, file_names in os.walk(path):
        dir_collection.extend(dir_names)

    return dir_collection

if __name__ == '__main__':
    choice = 1
    try:
        choice = int(sys.argv[1])
    except:
        pass

    if choice >= 1:
        print '\nRecursive listing of all paths in a dir:'
        for path in enumerate_paths():
            print path
    if choice >= 2:
        print '\nRecursive listing of all files in dir:'
        for single_file in enumerate_files():
            print single_file

    if choice >= 3:
        print '\nRecursive listing of all dirs in dir:'
        for directory in enumerate_dir():
            print directory
