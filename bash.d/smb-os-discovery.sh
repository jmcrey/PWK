#!/bin/bash

if [ -z "$1" ]; then
  echo "usage: ./os-discovery.sh <file-from-nmap>"
  exit 1
fi

for ip in $(cat $1 | grep "open" | cut -d " " -f 2); do
  nmap -v -p 139,445 --script smb-os-discovery.nse $ip -oG ./results.d/smb-os-discovery-$ip.txt
  cat ./results.d/smb-os-discovery-$ip.txt >> ./results.d/smb-os-discovery.txt
  rm ./results.d/smb-os-discovery-$ip.txt
done

