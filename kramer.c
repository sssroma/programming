#include <stdio.h>
#include <stdlib.h>

double determinant(double **a, int n){
    if (n == 0) {
        return 0.00;
    }
    if (n == 1) {
        return a[0][0];
    }
    if (n==2){
        return (double)(a[0][0] * a[1][1] - a[0][1]*a[1][0]);
    }
    else{
        double det=0.0;

        for (int i=0; i<n; i++){
            double **minor = malloc((n-1) * sizeof(double*));
            if (minor == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            for (int j=0; j<n-1; j++){
                minor[j] = malloc((n-1)*sizeof(double));
            } //выделяем память под миноры

            for (int j=1; j<n; j++){ //делаем миноры игнорируя 1 строку и i-й столбец
                int col=0;
                for (int k=0; k<n; k++){
                    if (k==i){
                        continue;
                    }
                    minor[j-1][col] = a[j][k];
                    col++;
                }
            }
            det += a[0][i]*determinant(minor, n-1)*((i%2==0)? 1 : -1); //считаем детерминант УРАА НАКОНЕЦ ТО
            for (int j=0; j<n-1; j++){
                free(minor[j]);
            }

            free(minor);
        }
        return det;
    }
}


double kram(int n, double **a, double arr2[n], int count){
    double **opr = malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++) {
        opr[i] = malloc(n * sizeof(double));
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (j==count-1){
                opr[i][j] = arr2[i];
            }
            else {
                opr[i][j] = a[i][j]; 
            }
            //printf("%lf ", opr[i][j]);
        }
        //printf("\n");
    }
    double det = determinant(opr, n);
    //printf("Переменная %d: ответ %lf\n\n", count, det);

    for (int i = 0; i < n; i++) {
        free(opr[i]);
    }
    free(opr);

    return det;
    }
    //lol пригодилось

int main(void){
    int n=0;
    printf("Введите размер матрицы N\n");
    scanf("%d", &n);
    
    double **a = malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(double));
    }

    double matrix_1[n];
    for (int i = 0; i < n; i++) {       // идём по строкам1
        for (int j = 0; j < n+1; j++) {   // идём по столбцам

            if (j==n){
                printf("Введите ответ [%d][%d]: ", i+1, j+1);
                scanf("%lf", &matrix_1[i]);
            }

            else{
                printf("Введите элемент матрицы [%d][%d]: ", i+1, j+1);
                scanf("%lf", &a[i][j]);
            }
        }
    }

    //выводим матрицу в консольку
    for (int i = 0; i < n; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) {
            printf("%lf ", a[i][j]);
        }
        printf(" | %lf", matrix_1[i]);
    printf("\n"); // переход
    }

    double all_det = determinant(a, n);
    printf("Детерминант матрицы: %lf\n\n", all_det);
    if (all_det != 0){
        for (int i=0; i<n; i++){
            printf("X[%d] = %.3f\n", i+1 ,kram(n, a, matrix_1, i+1)/all_det);
        }
    }
    else {
        printf("Система несовместна/ имеет бесконечное кол-во решений\n");
    }
}