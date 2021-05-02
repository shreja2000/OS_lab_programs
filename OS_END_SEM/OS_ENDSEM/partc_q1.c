#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <pthread.h>

// Number of Rows
#define M 3 
// Number of Columns
#define N 3

// Original Matrix A
int A[M][N] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
// Compound Matrix C
int C[M][N];

// Structure to hold the row index and the column index.
struct v
{
    int i;//row index
    int j; //column index
};

void *runner(void *param) //runner Function
{
    struct v *data = param;
    int row_num = 0, col_num = 0;

    // Create a temporary matrix that will hold the minor
    int temp[M - 1][N - 1];

    for (int i = 0; i < M; i++)
    {
        // if the row index is same as the value passed in the row index just ignore this iteration of row.
        if (i == (data->i))
        {
            ;
        }
        else
        {
            col_num = 0;
            for (int j = 0; j < N; j++)
            {
                // if the column index is same as the value passed in column index just ignore this iteration of column.

                if (j == (data->j))
                {
                    ; 
                }
                else
                {
                    temp[row_num][col_num] = A[i][j];
                    col_num++;
                }
            }
            row_num++; 

        }
    }
    // assign the value at row index i and column index j in the final matrix as the determinant of the minor matrix
    C[data->i][data->j] = temp[0][0] * temp[1][1] - temp[0][1] * temp[1][0];

    pthread_exit(0); 
}


int main()
{
    // define the row index and the column index
    // Declare pthreads
    pthread_t tid;
    pthread_attr_t attr;
    int i, j, count = 0;
    for (i = 0; i < M; i++)
    {   // row loop
        for (j = 0; j < N; j++)
        {
            
            struct v *data = (struct v*)malloc(sizeof(struct v));
            data->i = i;
            data->j = j;
            pthread_attr_init(&attr);
            pthread_create(&tid, &attr, runner, data);
        }
    }

    // join all the pthreads createda
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            pthread_join(tid, NULL);

        }
    }
    
    //print the original matrix
    printf("original matrix:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    
    // Printing the matrix
    printf("compound matrix:\n");

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }




    return 0;
}