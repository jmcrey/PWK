#!/bin/bash

if [ -z "$1" ]; then
    echo "usage: ./snmp-scan.sh <snmp-server-ips>"
    exit 1
fi

for ip in $(cat $1 | grep "public" | cut -d " " -f 1); do
  snmpwalk -c public -v1 $ip 1.3.6.1.2.1.6.13.1.3 >> ./results.d/snmpwalk-scan.txt
  snmp-check $ip >> ./results.d/snmp-check-scan.txt
done
