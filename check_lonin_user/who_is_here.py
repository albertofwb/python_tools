#!/usr/bin/env python

import time
import sys
import os
import simple_email
import subprocess

lock_file = '/tmp/send_email.lock'
del_time = "13:01"
today_hour = time.strftime("%H:%M")

# send email only once
if del_time == today_hour and os.path.exists(lock_file):
    os.remove(lock_file)

if os.path.exists(lock_file) is True:
    print "%s exist quit" %lock_file
    sys.exit()

# exit if no sessions with my username are found
output = subprocess.check_output('who')
if 'root' not in output:
    sys.exit()

words =  "Message sent at " + time.strftime("%a, %d %b %Y %H:%M:%S")
with open(lock_file, 'w') as fp:
    fp.write(words)

simple_email.send_email(title="jeff server new login", text=output)
