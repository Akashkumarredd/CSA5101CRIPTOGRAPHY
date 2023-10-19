#include <stdio.h>
void matrix_multiply(int mat1[][100], int mat2[][100], int result[][100], int r1, int c1, int r2, int c2) {
    int i, j, k;
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (k = 0; k < c1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
void print_matrix(int mat[][100], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int r1, c1, r2, c2;
    printf("enter the no of rows and columns for m 1: ");
    scanf("%d %d", &r1, &c1);
    printf("enter the no of rows and columns for matrix 2: ");
    scanf("%d %d", &r2, &c2);
    int matrix1[100][100],matrix2[100][100];
    printf("enter the elements of matrix 1:\n");
    int i,j;
    for ( i = 0; i < r1; i++) {
        for ( j = 0; j < c1; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("enter the elements of matrix 2:\n");
    for ( i = 0; i < r2; i++) {
        for ( j = 0; j < c2; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }
    int result_matrix[100][100];
    matrix_multiply(matrix1, matrix2, result_matrix, r1, c1, r2, c2);
    printf("\nresultant matrix multiplication\n");
    print_matrix(result_matrix, r1, c2);
    return 0;
}
