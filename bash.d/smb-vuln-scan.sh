#!/bin/bash

if [ -z "$1" ]; then
  echo "usage: ./smb-vuln-scan.sh <nmap-greppable-file>"
  exit 1
fi

for ip in $(cat $1); do
  nmap -v -p 139,445 --script=smb-vuln-ms08-067 --script-args=unsafe=1 $ip -oG ./results.d/vuln-ms08-067-$ip.txt
  cat ./results.d/vuln-ms08-067-$ip.txt >> ./resultds.d/vuln-ms08-067.txt
  rm ./results.d/vuln-ms08-067-$ip.txt
done
