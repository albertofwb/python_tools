#! /usr/bin/python3

# author:       Albertofwb
# email:        albertwb951@gmail.com
# edit time:    Thu 24/3/2016

import os
import sys
import crypt
import shutil
import subprocess
import config

'''
file_format:
(account)      (comment)	(company)
11042		albert		xaut
'''

USER_FILE   = config.user_dict['user_file']
PASS_FILE   = config.user_dict['pass_file']
GROUP_FILE  = config.user_dict['group_file']
HOME_DIR    = config.user_dict['home_dir']
TEMPLATE_DIR= config.user_dict['template']
DEBUG       = config.user_dict['debug']
total_files = [PASS_FILE, GROUP_FILE, USER_FILE]

def get_init_user_info():
    user_list = []
    fp =  open(USER_FILE)
    for line in fp:
        user_list.append(line.split(':')[0])
    return user_list

def run_command(app, target_file):
    if len(app) < 1 or len(target_file) < 1:
        return -1
    build_command = "{} {}".format(app, target_file)
    if 0 == subprocess.call(build_command, shell=True, stderr=subprocess.STDOUT):
        return True
    return False

def get_basic_user_info(user_file):
    user_info = []
    if not os.path.exists(user_file):
        print( "unable to open file: [%s]" %(user_file) )
        sys.exit(1)
    fp = open(user_file)
    for line in fp:
        line = line.strip()
        if len(line): user_info.append(line.split())
    return user_info


def copy_r(src_dir, dst_dir):
    if len(src_dir) < 1 or len(dst_dir) < 1:
        return False
    if not os.path.exists(dst_dir):
        os.mkdir(dst_dir)
    for single_file in os.listdir(src_dir):
        src_file  = os.path.join(src_dir, single_file)
        cur_file = os.path.join(dst_dir, single_file)
        if not os.path.exists(cur_file):
            print("copying %s to %s" %(src_file, cur_file))
            shutil.copyfile(src_file, cur_file)
    return True

def fullfill_user(userlist):
    src_dir = TEMPLATE_DIR
    for user in user_list:
        dst_dir = os.path.join(HOME_DIR, user)
        copy_r(src_dir, dst_dir)

#albert:x:1000:
def gen_pattern_for_newusers(user_list, show_process=False):
    init_uid = config.user_dict['init_uid']
    init_gid_name = config.user_dict['gid_name']
    init_gid = config.user_dict['init_gid']
    uid = init_uid
    result = ''
    shadow = ''
    group  = ''
    open_mode = 'r+'

    user_file = open(USER_FILE, open_mode)
    pass_file = open(PASS_FILE, open_mode)
    group_file= open(GROUP_FILE, open_mode)

    native_users = user_file.read()
    native_pass  = pass_file.read()
    native_group = group_file.read()

    if init_gid_name not in native_group:
        our_group = '{}:x:{}\n'.format(init_gid_name, init_gid)
        group_file.write(our_group)

    for (useraccount, username, usermajor) in user_list:
        group  = "{}:x:{}:\n".format(useraccount, uid)
        user_passwd = crypt.crypt(useraccount, "$6$XautNets")
        dst_dir = os.path.join(HOME_DIR, useraccount)
        copy_r(TEMPLATE_DIR, dst_dir)
        if not DEBUG:
            perm_command = "chown -R {}.{} {}".format(uid, init_gid, dst_dir)
            os.popen(perm_command)
        if useraccount not in native_users:
            result = "{}:x:{}:{}:XAUT-{}-{}:/home/{}:/bin/bash\n".format(useraccount, uid, init_gid, usermajor, username, useraccount )
            #print(result, shadow)
            user_file.write(result)
        if useraccount not in native_pass:
            shadow = "{}:{}:16879:0:99999:7:::\n".format(useraccount, user_passwd)
            pass_file.write(shadow)
        if str(uid) not in native_group:
            print("writing %s" % group)
            group_file.write(group)
        uid += 1
    print("creat users done")
    return True

def get_user_account(file_name):
    account_list = []
    if len(file_name) < 1:
        return False
    fp =  open(file_name)
    for line in fp:
        line = line.strip()
        if len(line) > 0: account_list.append(line.split()[0])
    return account_list

#TODO
def rm_r(user_list):
    for user in user_list:
        targetDir = os.path.join(HOME_DIR, user)
        if os.path.isdir(targetDir):
            command = "rm -frv {}".format(targetDir)
            os.popen(command)

def clean(user_list, show_process=True):
    rm_r(user_list)
    open_mode = "r+"
    for single_file in total_files:
        user_file = open(single_file, open_mode)
        users_info = user_file.readlines()
        user_file.seek(0)
        user_file.truncate(0)
        for line in users_info:
            account = line.split(':')[0]
            if account not in user_list:
                user_file.write(line)
            elif show_process:
                print("deleting %s from %s" %(line, single_file))
        user_file.close()

def backup(file_list):
    for single_file in file_list:
        back_name = single_file + '.bak'
        if os.path.isfile(single_file) and not os.path.exists(back_name):
            print("back up %s" %single_file)
            shutil.copyfile(single_file, back_name)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print( "Usage: %s   option   <filename>\n -c   clean user and data\n -m   make users and files\n" %(sys.argv[0]) )
        sys.exit(1)
    option    = sys.argv[1]
    file_name = sys.argv[2]

    if option == '-c':
        clean(get_user_account(file_name))
    elif option == '-m':
        backup(total_files)
        gen_pattern_for_newusers(get_basic_user_info(file_name))
