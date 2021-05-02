/*Implemented a serial version of the following: 
that merges the two sorted lists to generate the final sorted 
array.*/

//Random large input 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        

    printf("\n");

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

    sort(arr1,n1);//sort first half array
        printf("\nThe first list sorted\n");
        //print out the sorted array
        for(int i=0;i<n1;i++)
            printf("%d ",arr1[i]);
        printf("\n");

        sort(arr2,n2);//sort second half of the array
        //print out the sorted array
        printf("\nThe second list sorted\n");
        for(int i=0;i<n2;i++)
            printf("%d ",arr2[i]);
        printf("\n");

        //merge the two sorted arry into the final sorted array
    	printf("\nMerging the obtained lists  \n"); 
        merge_two_sorted_arrays(arr1,arr2,arr3,n1,n2);
        
        //printout the final sorted array
        for (int m = 0; m< n; ++m)
    		printf("%d ",arr3[m]);
		printf("\n");
    
    printf("\n");

    //end the clock 
    end_t = clock();

    //calculate runtime  and print it out
    total_t = (1.0)*(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t );
    printf("Exiting of the program...\n");

}