#! /usr/bin/python
#encoding: utf-8
import os

class diskwalk(object):
    '''API for getting directory walking collections'''
    def __init__(self, path):
        self.path = path

    def enumerate_paths(self):
        # Returns the path to all the files in a directory  recursively.
        path_collection = []
        for dir_path, dir_names, file_names, in os.walk(self.path):
            for file in file_names:
                fullpath = os.path.join(dir_path, file)
                path_collection.append(fullpath)
        return path_collection

    def enumerate_files(self):
        # Return all the files in a directory as a list
        file_collection = []
        for dir_path, dir_names, file_names in os.walk(self.path):
            file_collection.extend(dir_names)
        return file_collection

    def enumerate_dir(self):
        # Return all the directories in a directory as a list
        dir_collection = []
        for dir_path, dir_names, file_names in os.walk(self.path):
            dir_collection.extend(dir_names)
        return dir_collection
