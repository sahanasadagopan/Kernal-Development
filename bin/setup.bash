#!/bin/bash

#installing all the basic packages
sudo apt-get update
sudo apt-get install git-all
sudo apt-get vim

#running all the .bash and .bash_profile scripts

sudo ./bashrc
sudo ./bash_profile

#building the kernel again
sudo git clone https://github.com/sahanasadagopan/Kernal-Development.git
sudo /home/"$USER"/bin/build_kernel

 
