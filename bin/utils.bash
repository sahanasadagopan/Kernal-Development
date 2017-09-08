#!/bin/bash
#Find the version of the operating system
cat /etc/*-release
#Operating system 
uname -o
#kernal version
uname -v
#Information on kernal build
cat /proc/version
#gives the time of the build too
#builds the system architecture
uname -i 
