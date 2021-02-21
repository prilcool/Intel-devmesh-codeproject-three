
//==============================================================
// Copyright © 2021 Intel Corporation
// Author:Prilvesh Krishna
// Email:prilcool@hotmail.com    
// Linkedin:https://www.linkedin.com/in/prilvesh-k-4349ba54/
// Date:03/02/2020    
// SPDX-License-Identifier: MIT
// =============================================================



#include<CL/sycl.hpp>
#include<array>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<limits>
#include <chrono>
#include <vector>
#include <string>
#include "md5.h"

using namespace sycl;


int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    //the size of your insecure password  guess list
    constexpr int N=6; 
    
    //select device to perform operations with  we selected cpu_selector
    
     // if you select a GPU device than Device: Intel(R) Graphics Gen9 [0x3e96] will process in 1 second.
     queue q(cpu_selector{});
    
    //if you select a CPU device than Device: Intel(R) Xeon(R) E-2176G CPU @ 3.70GHz will process in 3 seconds.
    //to use cpu un comment the below and comment the above.
    //queue q(=gpu_selector{});
 
    
    std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;


    // Allocate shared memory space 
      int*cracked_passwords=malloc_shared<int>(N, q); //to hold cracked passwords 


    // this are the names
    const char *our_database_to_hack_usernames[]={"Tommy", "Angelina", "Rick", "Donna","Steve","Kim"};
    
    // this are the md5 hashed  passwords from the database this are user passwords that we will try and crack.
     const char *our_database_to_hack[]={"be6a7b58918d6a86dcd7165105a55735","9c5e6de58e6d4db5b6407ff633a731ea",
                                         "91f279d26889d5383b8e44a3b17126f6","39efb1a1cb8b2ecb609016ccf672f2ba",
                                         "73b1766d87521e37862e2303a1e0b217","05f4016d70e4c40860ae3698ccf6756b"}; 
   
    
    // We load data into a array for ourlist of common insecure passwords ,this are our guesses
     std::string insecure_password_list[]={"stevey_wonder#54321","Hockey_rocks_1234!","Canada@7777$","Welcome@2020$","Pineapple@1234!","Password_@1234!"}; 
    
    
    // we convert each value of the list using MD5 alogrithm and so on example,
    // std::string index_zero=md5(insecure_password_list[0]);
    // std::cout<<"An example of "<<insecure_password_list[0] <<" When MD5 hashed is "<< index_zero<<std::endl;
    
    // so below is a preconverted MD5 list of the above loaded into an array .
   const char *insecure_password_list_hashed[] = {"e78258ed4cb53b88be9362fd439ded9d","42d717e8f76610bee6a103559135c577","3802627cb2fc0e1b993a636d229cfa3a",
                                                  "05f4016d70e4c40860ae3698ccf6756b","d6fc3939b3323b30564d01a44abb0bcb","be6a7b58918d6a86dcd7165105a55735"};
   

   //next we select a single password  md5 hash from our Database that we want to crack
   // you can change the  user_index_from_databse value in this example between 0  to five  if you want to choose another user whose password you want to crack.
    
    int user_index_from_databse=5;
    std::string user=our_database_to_hack_usernames[user_index_from_databse];
    const char *password_to_crack=our_database_to_hack[user_index_from_databse];
   
    for (int i =0; i < N; i++) {
        i=i;
    
    }

    
    //we begin the cracking by doing a comparison to see if our_password_guess matches  password_to_crack
    // if our password matches it means its insecure and its index  stored into our cracked_passwords denoted by number 2. 

    
    q.parallel_for(range<1>(N), [=](id<1> i) {
        

 
    const char * our_password_guess=insecure_password_list_hashed[i];
                
        
       
        int password_found=0;  
        
        int password_not_found=0;
         for(int k=0;k<32;k++){

          if(our_password_guess[k]==password_to_crack[k]){ 
                password_found++; 
           }else{
               password_not_found--; 
        }
        }
       
          if (password_found==32){
           cracked_passwords[i]=2;  //password found 
            
        }
        else{
         cracked_passwords[i]=1;  //password not found 
        }
        
       
        

        
    }).wait();
          

    // now we output 
     int flag_no_password_cracked=0;
      std::cout<<"*********************************************"<<std::endl;      

    for (int i = 0; i < N; i++) {
        if(cracked_passwords[i]==2){
      std::cout<<" "<<std::endl;       
      std::cout<<"FOUND IT "<<std::endl;         
      std::cout<<"Success !! Password Cracked At index "<<i<<" in common passwords list For Hash "<<insecure_password_list_hashed[i]<<" the password was "<<insecure_password_list[i]<<std::endl; 
      std::cout<<"Notify user "<<user<<" to change password immediatly as it's insecure"<<std::endl; 
      std::cout<<"*********************************************"<<std::endl;      
 
      flag_no_password_cracked=2;
        }else{
            
        std::cout<<"Not Matched "<<i<<insecure_password_list_hashed[i]<<" tried to crack with "<<password_to_crack<<std::endl; 
 
        }
    }
  
    if(flag_no_password_cracked==0){
        
            std::cout<<"Congrats password not cracked ,no insecure password found for user "<<user<<std::endl;  
            
    }
    
    free(cracked_passwords, q);
    return 0;
}






