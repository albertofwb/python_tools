#! /usr/bin/env python
#encoding: utf-8
import os
import sys
import smtplib
import zipfile
import tempfile
import email.MIMEBase
import email.MIMEText
import email.MIMEMultipart

From = "2932716209@qq.com"
To = "wn002102095@126.com"

def make_accessory(fine_name):
        # 构造MIMEBase对象做为文件附件内容并附加到根容器
        contype = 'application/octet-stream'
        maintype, subtype = contype.split('/', 1)
        file_msg = email.MIMEBase.MIMEBase(maintype, subtype)
        data = open(file_name, 'rb')
        file_msg.set_payload(data.read())
        data.close()
        email.Encoders.encode_base64(file_msg)
        ## 设置附件头
        file_msg.add_header('Content-Disposition', 'attachment', filename=file_name)
        return file_msg

def send_email(sender=From, recviers=To, title="This is title", text="this is a test text to text mime", data=None):
        server = smtplib.SMTP("smtp.qq.com")
        server.login("123456789","123456") #仅smtp服务器需要验证时
        # 构造MIMEMultipart对象做为根容器
        main_msg = email.MIMEMultipart.MIMEMultipart()
        # 构造MIMEText对象做为邮件显示内容并附加到根容器
        text_msg = email.MIMEText.MIMEText(text)
        main_msg.attach(text_msg)

        if data is not None:
                main_msg.attach(data)
        # 设置根容器属性
        main_msg['From'] = sender
        main_msg['To'] = recviers
        main_msg['Subject'] = title
        main_msg['Date'] = email.Utils.formatdate( )
        # 得到格式化后的完整文本
        fullText = main_msg.as_string()
        server.sendmail(From, To.split(';'), fullText)
        server.quit()

# 用smtp发送邮件
if __name__ == '__main__':
        print 'Sending email to %s' %(To)
        #send_email(title = 'I wanna a photo', make_accessory(upload_file_name))
        send_email(title='send_myself', "test email")
        print 'Done'
