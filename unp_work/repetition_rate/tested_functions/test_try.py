#! /usr/bin/python

def func_1():
    try:
        1/0
    except Exception as error:
        print error
    finally:
        print "finally"


def func_2():
    try:
        1/0

        print error
    print "finally"

func_1()
func_2()
