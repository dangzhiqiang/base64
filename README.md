# base64
base64 encode and decode for string

usage
=====
    Usage:
	    ./base64 --encode            # encode strings which you input
	    ./base64 --decode            # decode strings which you input
	    ./base64 --help or -h        # show this help infomation
	
lib
=====
    funciton:
      char *base64_encode(const char *data, int data_len)
      char *base64_decode(const char *data, int *length)
