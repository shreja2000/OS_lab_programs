/* Matrix multiplication using both single thread and multithreading.
 * The purpose is to compare the speed of each system.
 *
 * Author: Enrique Izaguirre-Valdés
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int rowsA, rowsB, rowsC, colsA, colsB, colsC;
int **A;
int **B;
int **C;
int done[21];


int** createMatrix(int **X, short rows, short cols) {
     int i, j;
     X = malloc(sizeof(int*) * rows);
     for (i = 0; i < rows; i++) {
          X[i] = malloc(sizeof(int) * cols);
         /* for (j = 0; j < cols; j++) {
               printf("Element[%d][%d] = ", i, j);
               scanf("%d", &X[i][j]);
          }*/
     }
     return X;
}

int** populateMatrix(int **X, short rows, short cols) {
     int i, j; 
     for (i = 0; i < rows; i++) {
          for (j = 0; j < cols; j++) {
               printf("Element[%d][%d] = ", i, j);
               scanf("%d", &X[i][j]);
          }
     }
     return X;
}

void matrixPrint(int **X, short rows, short cols) {
     /* Printing the Matrix */
    // printf("Entering to print matrix\n");
    // printf("rows = %d, cols = %d\n", rows, cols);
     unsigned short i, j;
     for (i = 0; i < rows; i++) {
          for (j = 0; j < cols; j++) {
               if (j == 0) printf("| ");
               printf("%4d  ", X[i][j]);
               if (j == (cols - 1)) printf("|\n");
               //printf("A[%d][%d] = %d\n", i, j, X[i][j]);
          }
     }
     //printf("Finishing printing Matrix\n");
}

void *rowMult(void *row) {
     int i = (int) row;
     int j, m;
     printf("Row[%d]\n", i);
     for (j = 0; j < colsC; j++) {
          C[i][j] = 0;       // Clearing out before doing operations.
          for (m = 0; m < colsA; m++)
               C[i][j] += A[i][m] * B[m][j];
      }

      printf("Row[%d] done\n", i);
      return NULL;
}

int main() {
     //int A[3][2] = {{3,6}, {9,8}, {0,1}};
/*     int rowsA, rowsB, rowsC, colsA, colsB, colsC;
     int **A;
     int **B;
     int **C;
 */
     printf("Matrix Multiplication\n\n");
     printf("Enter the Matrix A:\n");
     printf("Number of rows: ");
     scanf("%d", &rowsA);
     printf("Number of columns: ");
     scanf("%d", &colsA);
     printf("Creating Matrix A..\n");
     A = createMatrix(A, rowsA, colsA);
     A = populateMatrix(A, rowsA, colsA);
     printf("Matrix A complete\n\n");

     printf("Enter the Matrix B:\n");
     printf("Number of rows: ");
     scanf("%d", &rowsB);
     printf("Number of columns: ");
     scanf("%d", &colsB);
     printf("Verifying data ..\n");
     if ((rowsA != colsB) || (rowsB != colsA)) {
          printf("This is not a valid Matrix operation!\n");
          printf("Number of rows of A should be equal to the number of columns of B,\n");
          printf("and the number of columns of A should be equal to the number of rows of B.\n");
          printf("to be able to multiply both matrixes.\n");
          return;
     }
     printf("Creating Matrix B..\n");
     B = createMatrix(B, rowsB, colsB);
     B = populateMatrix(B, rowsB, colsB);
     printf("Matrix B complete\n\n");

     printf("Printing Matrix A:\n");
     matrixPrint(A, rowsA, colsA);
     printf("\n\n");
     printf("Printing Matrix B:\n");
     matrixPrint(B, rowsB, colsB);
     printf("Data complete, initiating functionality...\n\n");

     printf("Creating Matrix C..\n");
     rowsC = rowsA;
     colsC = colsB;
     int i, j, m;
     C = createMatrix(C, rowsC, colsC);
     /* Debugging code */
     /*for (i = 0; i < rowsC; i++)
           for (j = 0; j < colsC; j++)
               C[i][j] = 0;
     matrixPrint(C, rowsC, colsC);*/

     printf("Carrying out Matrix Multiplication..\n");
     
     for (i = 0; i < rowsC; i++)
          for (j = 0; j < colsC; j++) {
              C[i][j] = 0;       // Clearing out before doing operations.
              for (m = 0; m < colsA; m++)
                   C[i][j] += A[i][m] * B[m][j];
          }

     printf("Multiplication complete.\n");
     printf("Printing Matrix C..\n");
     matrixPrint(C, rowsC, colsC);

     printf("\n");
     printf("Now do the same using threads: one thread for each row..\n");
     /* Clear target matrix first */
     for (i = 0; i < rowsC; i++)
          for (j = 0; j < colsC; j++)
              C[i][j] = 0;     
     pthread_t ths[21];
     //for (i = 0; i < 21; i++) done[i] = 0;
     /* Creating the threads: one per row: */
     for (i = 0; i < rowsC; i++) {
          printf("i = %d\n", i);
          if ( pthread_create( &ths[i], NULL, rowMult, i) ) {
              printf("error creating thread.");
              abort();
          }
     }
     
     for (i = 0; i < rowsC; i++)
         // while (done[i]) {
               if ( pthread_join ( ths[i], NULL ) ) {
                   printf("error joining thread.");
                   abort();
               }
         // }

     printf("Multiplication complete.\n");
     printf("Printing Matrix C..\n");
     matrixPrint(C, rowsC, colsC);
     return 0;
}
