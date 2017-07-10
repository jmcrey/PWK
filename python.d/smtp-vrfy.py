#!/usr/bin/python

import socket, sys

# Enough Args?
if len(sys.argv) != 3:
	print "usage: smtp-vrfy.py <ips> <usrnames>"
	sys.exit(1)

# File names
ips = sys.argv[1]
usrnames = sys.argv[2]

# Open IP file
with open(ips, 'r') as ips:
  for ip in ips:

   # Make socket
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)

   # Connect to IP by line
    print ip
    connect = s.connect((ip, 25))

   # Grab banner to ensure connection
    banner = s.recv(1024)
    print banner

   # Test user names
    with open(usrnames, 'r') as names:
      for name in names:
	print 'VRFY ' + name + '\r\n'
	s.send('VRFY ' + name + '\r\n')
     	result=s.recv(1024)
	print result

   # Clean up
    names.close()
    s.close()

# Clean up
ips.close()
