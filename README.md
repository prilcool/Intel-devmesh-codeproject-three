# Intel-devmesh-codeproject-three
This article shows you how to use Intel's  DPC++ to crack insecure  user passwords based on MD5 hashes. It shows you a practical way to identify and mitigate insecure password risks from your organization.


## Usage instructions :
Copy the entire structure including all files to  Intel dev cloud .

Ensure that the  Python 3.7 (Intel OneApi)  kernal is running

Ensure that you are using the q file ,crack_md5_password.sh  that is provided with this sourcecode.

Ensure that file exist in  lab/crack_md5_password.cpp


Run the following  jupyter notebook  Interest-on-account-audit-onemillion_records.ipynb

## Than Run  the following command
! chmod 755 q; chmod 755 crack_md5_password.sh;if [ -x "$(command -v qsub)" ]; then ./q regression.sh; else ./crack_md5_password.sh; fi 


## On successfull run :

You should be able to crack users passwords for those who have insecure passwords for example  Kim's  password 




## Result

![alt text](https://github.com/prilcool/Intel-devmesh-codeproject-three/blob/main/Assets/out.PNG)

