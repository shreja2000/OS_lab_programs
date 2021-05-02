/*Implement a multiprocessing version of the following: 2 processes 
that sort an original array into two sorted lists and a third merging 
processes that merges the two sorted lists to generate the final sorted 
array.*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define RD_END 0
#define WR_END 1

//function to sort an array
void swap(int *xp, int *yp){ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void sort(int arr[], int n) {
   for (int i=0;i< n-1;i++)       
       for (int j= 0;j< n-i-1;j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

//function to merge two sorted array
void merge_two_sorted_arrays(int arr1[], int arr2[], int arr3[], int m, int n){
    int i,j,k;
    i = j = k = 0;
    for(i=0;i< m && j < n;){
        if(arr1[i] < arr2[j]){
            arr3[k] = arr1[i];
             k++;
             i++;
    }
        else{
            arr3[k] = arr2[j];
            k++;
            j++;
        }
    }
    
    while(i < m){
        arr3[k] = arr1[i];
        k++;
        i++;
    }
    
    while(j < n){
        arr3[k] = arr2[j];
        k++;
        j++;
    }
}


//Driver code
int main(int argc,char *argv[]){
    //init clock
    float start_t, end_t, total_t;

    //start the clock
    start_t = clock();

    
    srand(time(0));
        int n=10000,arr[10000];
        for(int i=0;i<n;i++)
            arr[i]=rand()%100;
        

    int n1=n/2;//first array size
    int arr1[n1];//first array init

    for (int i = 0; i < n1; ++i)
		arr1[i]=arr[i];
    
    int n2=n-n1;//second array size
	int arr2[n2],p=0;//second array init
	for(int i=n/2;i<n;i++){
		arr2[p]=arr[i];
		p++;
	}
 

    //Output variable declarations
    int arr3[n];//Output array

   
    //Create two pipes for parent and child read and write.
    int p1fd[2],p2fd[2];
   
    //creation and validation of pipe
    if(pipe(p1fd)==-1){
        fprintf(stderr,"Error:Unable to create pipe p1\n");
        return 1;
    }
    if(pipe(p2fd)==-1){
        fprintf(stderr,"Error:Unable to create pipe p2\n");
        return 1;
    }

    //fork
    int pid1=fork();
    //Validation of the fork
    if(pid1<0)
        fprintf(stderr,"Error:fork of process1 failed!!\n");
    
    
    if(pid1==0){
        //close unwanted pipes
        close(p1fd[RD_END]);
        //sort the first array
        sort(arr1,n1);

        printf("\nThe first list sorted @ process1....\n");
        for(int i=0;i<n1;i++)
            printf("%d ",arr1[i]);
        printf("\n");
        //write into the pipe
        write(p1fd[WR_END],&arr1,sizeof(arr1));
		exit(0);

    }
    //create the second process
    int pid2=fork();

    if(pid2<0)
        fprintf(stderr,"Error:fork of process2 failed!!\n");
    
    if(pid2==0){
        //close unwanted pipes
        close(p2fd[RD_END]);

        //sort the second array
        sort(arr2,n2);

        printf("\nThe second list sorted @ process2...\n");
        for(int i=0;i<n2;i++)
            printf("%d ",arr2[i]);
        printf("\n");
        //write into the pipe
        write(p2fd[WR_END],&arr2,sizeof(arr2));
		exit(0);

    }
    
    //third process
    if(pid1){

        wait(NULL);
        //close unwanted pipes
        close(p1fd[WR_END]);
        close(p2fd[WR_END]);

        //create the input arrays to receive from the process 1 and 2
		int arr4[n1],arr5[n2];
		
        // read from pipe 1
        read(p1fd[RD_END],&arr4,sizeof(arr4));
		
        //print out what is read
        printf("\nThe first sorted list received @ process3: \n");
		for (int i = 0; i < n1; ++i){
    		printf("%d ",arr4[i]);
    	}

        //read from pipe 2
		read(p2fd[RD_END],&arr5,sizeof(arr5));
		
        //print out what is read 
        printf("\nThe second sorted list received @ process3: \n");
		for (int i = 0; i < n2; ++i){
    		printf("%d ",arr5[i]);
    	}


        //merge the two sorted arrays into a new sorted array
        printf("\nMerging the obtained lists @ process3 \n"); 
        merge_two_sorted_arrays(arr4,arr5,arr3,n1,n2);

        //print out the  final sorted array        
        for (int m = 0; m< n; ++m)
    		printf("%d ",arr3[m]);
		printf("\n");

    }

    printf("\n");

    //end the clock 
    end_t = clock();

    //calculate runtime  and print it out
    total_t = (1.0)*(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t );
    printf("Exiting of the program...\n");

}