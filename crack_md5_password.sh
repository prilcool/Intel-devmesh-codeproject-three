#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling DPCPP_Essentials to crack md5 encryption and reveal insecure passwords
dpcpp lab/crack_md5_password.cpp lab/md5.cpp -o bin/crack_md5_password -std=c++11
if [ $? -eq 0 ]; then bin/crack_md5_password; fi

