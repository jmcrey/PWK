#!/bin/bash

nmap -v -p 139,445 10.11.1.1-254 -oG ./results.d/smb-running.txt

if [ $1 == "-u" ]; then
  for ip in $(cat ./results.d/smb-running.txt | grep "open" | cut -d " " -f 2); do
    nmap --script smb-enum-users.nse -p 445 $ip >> ./results.d/smb-users-scan-$ip.txt
  done
fi

