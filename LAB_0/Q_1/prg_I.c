//can copy from src to dest files but only one src and dest file.
//and this function can copy any kind of file.

#include<stdio.h>
int main(int argc,char *argv[]){
    int i,srcfile,destfile,read,write;
    if(argc<3){
        printf("Too less arguments\n");
        printf("Usage:cp <src_file> <dest_file>\n");
        return 0;
    }
    if( argc > 3 || argv[1]== "--help"  ){
        printf("Too many arguments\n");
        printf("Usage:cp <src_file> <dest_file>\n");
        return 0;
    }
 FILE *srcptr,*destptr;
 srcptr=fopen(argv[1],"rb");
 destptr=fopen(argv[2],"wb");
 char c = fgetc(srcptr); 
    while (c != EOF) 
    { 
        fputc(c, destptr); 
        c = fgetc(srcptr); 
    } 
  
    printf("\nContents copied to %s", argv[2]);
    printf("\n"); 
  
    fclose(srcptr); 
    fclose(destptr); 
    return 0;
}