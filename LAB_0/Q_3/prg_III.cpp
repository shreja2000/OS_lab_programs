
#include<iostream>
#include<stdlib.h>
using namespace std;
//function for sort
//function overloading for different types
void sort(char *a,int n,int f);
void sort(float *a,int n,int f);
void sort(int *a,int n,int f);
//input validation error msgs
char err[]="Too less or too may arguments please enter in the format specified below:\n ./multisort <type> <ascd/dscd><sizeof(input_arr)> <input_arr[0:size-1]>\ntype:\nc for char\ni for int\nf for float\n1 for ascd\n0 for dscd\n";
char err1[]="Invalid value\n1 for ascd\n2 for dscd";
int main(int argc,char *argv[]){
    int n,f;
    char t;
    char a[100];float b[100];int c[100];
    if (argc==0|argc==1|argc==2|argc==3){
        cout<<err;
        exit(-1);
    }

    f =atoi(argv[2]);
    cout,"\n";
    t=argv[1][0];
    n= atoi(argv[3]);
    //input validation
    if(n==0){
        cout<<"sizeof input array zero exiting...\n";
        exit(0);
    }
    if (argc!=n+4){
    cout<<err;
    exit(-1);
        
    }
    switch(t){
       case 'i':{
            for(int i=0;i<n;i++){
                c[i]=atoi(argv[i+4]);
            }
            sort(c,n,f);       
            break;
        }
       case 'c':{
            for(int i=0;i<n;i++){
                a[i]=argv[i+4][0];
            }
            sort(a,n,f);
            break;
        }         
        case 'f':{
            for(int i=0;i<n;i++){
                b[i]=atof(argv[i+4]);         
        }
            sort(b,n,f);        
            break;
        }
    default:{
            cout<<"Invalid type\nThe valid input types are\nc for char\ni for int\nf for float\n";   
            break;
        }
    }
}
void sort(char *a,int n,int f){
    
      for(int i =0;i<n;i++){
          for(int j=i;j<n;j++){
              char temp;
              if(a[j]<a[i]){
              temp = a[j]; 
              a[j] = a[i];
              a[i] = temp;
                }
            }
      }
 if(f==1){
     cout<<"Printng ascd : ";
     for(int i=0;i<n;i++)
     cout<<a[i]<<"    ";
     cout<<"\n";
 }
 else if(f==0)
 {    cout<<"Printng dscd : ";
      for(int i=0;i<n;i++)
     cout<<a[n-i-1]<<"   ";
     cout<<"\n";
 }
 else
 {
     cout<<err1;
 }
 
 
}
void sort(float *a,int n,int f){
    
      for(int i =0;i<n;i++){
          for(int j=i;j<n;j++){
              float temp;
              if(a[j]<a[i]){
              temp = a[j]; 
              a[j] = a[i];
              a[i] = temp;
                }
            }
      }
 if(f==1){
     cout<<"Printng ascd : ";
     for(int i=0;i<n;i++)
     cout<<a[i]<<"   ";
     cout<<"\n";
 }
 else if(f==0)
 {
     cout<<"Printng dscd : ";
      for(int i=0;i<n;i++)
     cout<<a[n-i-1]<<"   ";
     cout<<"\n";
 }
 else
 {
     cout<<err1;
 }
 
 
}
void sort(int *a,int n,int f){
    
      for(int i =0;i<n;i++){
          for(int j=i;j<n;j++){
              int temp;
              if(a[j]<a[i]){
              temp = a[j]; 
              a[j] = a[i];
              a[i] = temp;
                }
            }
      }
 if(f==1){
     cout<<"Printng ascd : ";
     for(int i=0;i<n;i++)
     cout<<a[i]<<"   ";
     cout<<"\n";
 }
 else if(f==0)
 {
     cout<<"Printng dscd : ";
      for(int i=0;i<n;i++)
     cout<<a[n-i-1]<<"   ";
     cout<<"\n";
 }
 else
 {
     cout<<err1;
 }
 
 
}