#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "usage: ./ip-scan.sh <file-with-IPs-from-nmap> <port-to-scan>"
    exit 1
fi

for ip in $(cat $1 | grep "Host" | cut -d " " -f 2); do
  nmap -p $2 $ip -oG ./results.d/open-xports.txt
done

