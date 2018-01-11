# base64
base64 encode and decode for string

usage
-----
    Usage:
	    ./base64 --encode            # encode strings which you input
	    ./base64 --decode            # decode strings which you input
	    ./base64 --help or -h        # show this help infomation
	
lib
-----
    funciton:
      char *base64_encode(const char *data, int data_len)
      char *base64_decode(const char *data, int *length)
      
note
-----
	这是一个准线上级别的工具，用于深入理解base64编码。
	更好的选择是使用系统自带的base64小程序，或者直接拿其源代码来用。
	在centos/rhel系统下，由coreutils安装包提供base64程序，默认已经安装。
    
