#!/bin/bash
#Opersting system type
cat /etc/*-release
#Operating system 
uname -o
#kernal version
uname -v
#Information on kernal build
uname -a
#gcc Build version
cat /proc/version
#gives the time of the build too
cat /proc/sys/kernel/version
#builds the system architecture
uname -i
lscpu
