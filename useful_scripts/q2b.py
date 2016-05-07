import os
import sys

def strQ2B(ustring):
    """全角转半角"""
    rstring = ""
    for uchar in ustring:
        inside_code=ord(uchar)
        if inside_code == 12288:                              #全角空格直接转换            
            inside_code = 32 
        elif (inside_code >= 65281 and inside_code <= 65374): #全角字符（除空格）根据关系转化
            inside_code -= 65248

        rstring += chr(inside_code)
    return rstring
    
def strB2Q(ustring):
    """半角转全角"""
    rstring = ""
    for uchar in ustring:
        inside_code=ord(uchar)
        if inside_code == 32:                                 #半角空格直接转化                  
            inside_code = 12288
        elif inside_code >= 32 and inside_code <= 126:        #半角字符（除空格）根据关系转化
            inside_code += 65248

        rstring += chr(inside_code)
    return rstring

if __name__ == "__main__":
    file_names = ""
    src_text   = ""
    if len(sys.argv) < 2:
        print("Usage: %s <target-file-name>" %sys.argv[0])
        sys.exit(1)
    
    file_names = sys.argv[1]

    if not os.path.exists(sys.argv[1]):
        file_names = sys.argv[1]
        sys.exit(1)

    # print("get file: %s" %file_names)
    with open(file_names) as fp:
        src_text = fp.read()

    print(strQ2B(src_text))
