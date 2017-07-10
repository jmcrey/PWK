#!/bin/bash

for dnsname in $(host -t ns megacorpone.com | cut -d " " -f 4); do
  host -l megacorpone.com $dnsname > ./results.d/axfr.txt
done
