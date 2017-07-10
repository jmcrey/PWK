#!/bin/bash

iptables -I INPUT 1 -s 10.11.1.202 -j ACCEPT #fill in xxx with target host
iptables -I OUTPUT 1 -d 10.11.1.202 -j ACCEPT #fill in xxx with target host
iptables -Z
