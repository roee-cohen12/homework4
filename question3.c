#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define N (100)
#define M (100)

void printMatrix(double a[][M], int n, int m) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }
}

bool inputMatrix(double a[][M], int n, int m) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%lf ", a[i][j]) != 1) {
                return false;
            }
        }
    }
    return true;
}

void swapRows(double* r1s, double* r1e, double* r2s, double* r2e) {

    double* temp_s = r1s;
    double* temp_e = r1e;
    r1s = r2s;
    r1e = r2e;
    r2s = temp_s;
    r2e = temp_e;
}

void multiplyRow(double* rs, double* re, double scalar) {

    double* temp_p = rs;
    while (temp_p <= re) {
        *temp_p *= scalar;
        temp_p++;
    }
}

void addRows(double* r1s, double* r1e, double* r2s, double* r2e, double s){

    double* temp_row_to_add = malloc((r2e - r2s)* sizeof(double));
    if (temp_row_to_add == NULL) {
        return; //memory allocation failed
    }
    multiplyRow(temp_row_to_add, r2e, s);
    double* temp_r1_p = r1s;
    while (temp_r1_p <= r1e) {
        *temp_r1_p *= *temp_row_to_add;
        temp_r1_p++;
        temp_row_to_add++;
    }
    free(temp_row_to_add);
}

void findLeadElement(double a[][M], int n, int m, int *r, int *c, bool *res) {

    if (a[0][0] != 0) {
        *res = true;
        *r = 0;
        *c = 0;
        return;
    }
    while (*a == 0) { //find first lead element
        a++;
    }
    int min_pos_row = 0, min_pos_col = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0) {
                if (j < min_pos_col) {
                    min_pos_row = i;
                    min_pos_col = j;
                }
            }
        }
    }
    if (min_pos_row == 0 && min_pos_col == 0) {
        *res = false;
        *r = 0;
        *c = 0;
    } else {
        *res = true;
        *r = min_pos_row;
        *c = min_pos_col;
    }
}

void reduceRows(double a[][M], int n, int m) {
    for (int i = 0; i < n; i++) {
        int lead_r, lead_c;
        bool found;

        /*
        TODO - call findLeadElement
        */
        findLeadElement(a, n, m, &lead_r, &lead_c, &found);
        if (!found)
            break;
        int cur_r = i + lead_r;
        if (cur_r != i) {
            /*
            TODO - call swapRows
            */
            swapRows();
        }
        double pivot_val = a[i][lead_c];
        /*
            multiplyRow
        */
        for (int k = i + 1; k < n; k++) {
            double factor = -a[k][lead_c];
            if (factor != 0){
                /*
                    TODO - addRows
                */
                addRows()
            }
        }
    }
}

int main() {
    int n, m;
    double matrix[N][M];
    printf("Enter number of rows (n) and columns (m):\n");
    // TODO: Read the number of rows (n) and columns (m) from the user.
    // Ensure that n and m are positive and that m <= M and n <= N.
    scanf("%d %d", n, m);
    if (n <= 0 || n > N || m <= 0 || m > M) {
        printf("Invalid matrix size.\n");
        return 1;
    }
    printf("Enter the matrix elements:\n");

    // TODO: Call inputMatrix to fill the matrix with values from the user.
    // If the function returns false, print the error message and return 1.
    if (!inputMatrix(matrix, n, m)) {
        printf("Invalid matrix elements\n");
        return 1;
    }

    printf("Original Matrix:");
    // TODO: Call printMatrix.
    printMatrix(matrix, n, m);
    // TODO: Call reduceRows.
    reduceRows(matrix, n, m);

    printf("Reduced Matrix:\n");
    // TODO: Call printMatrix again.
    printMatrix(matrix, n, m);
}