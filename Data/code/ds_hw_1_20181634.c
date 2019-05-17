#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, column, value;
} Term;

#define MAX_TERMS 1024

void readMatrix(FILE *fp, Term a[]) {
    int r, c;
    fscanf(fp, "%d%d", &r, &c);

    a[0].row = r, a[0].column = c, a[0].value = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int x;
            fscanf(fp, "%d", &x);
            if (x == 0) continue;

            (a[0].value)++;
            int idx = a[0].value;
            a[idx].row = i, a[idx].column = j, a[idx].value = x;
        }
    }
}

void printMatrix(Term a[]) {
    for (int i = 0; i <= a[0].value; i++) {
        printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
    }
}

void matrixAdd(Term a[], Term b[], Term c[]) {
    c[0].row = a[0].row, c[0].column = a[0].column, c[0].value = 0;

    int i = 1, j = 1;

    while (i <= a[0].value && j <= b[0].value) {
        (c[0].value)++;
        int idx = c[0].value;
        if (a[i].row == b[j].row) {
            if (a[i].column == b[j].column) {
                c[idx].row = a[i].row, c[idx].column = a[i].column, c[idx].value = a[i].value + b[j].value;
                i++, j++;
            } else if (a[i].column < b[j].column) {
                c[idx].row = a[i].row, c[idx].column = a[i].column, c[idx].value = a[i].value;
                i++;
            } else { // a[i].column > b[j].column
                c[idx].row = b[j].row, c[idx].column = b[j].column, c[idx].value = b[j].value;
                j++;
            }
        } else if (a[i].row < b[i].row) {
            c[idx].row = a[i].row, c[idx].column = a[i].column, c[idx].value = a[i].value;
            i++;
        } else { // a[i].row > b[j].row
            c[idx].row = b[j].row, c[idx].column = b[j].column, c[idx].value = b[j].value;
            j++;
        }
    }

    while (i <= a[0].value) {
        (c[0].value)++;
        int idx = c[0].value;
        c[idx].row = a[i].row, c[idx].column = a[i].column, c[idx].value = a[i].value;
        i++;
    }

    while (j <= b[0].value) {
        (c[0].value)++;
        int idx = c[0].value;
        c[idx].row = b[j].row, c[idx].column = b[j].column, c[idx].value = b[j].value;
        j++;
    }
}

int main() {
    Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

    FILE *fp = fopen("A.txt", "r");
    readMatrix(fp, a);
    fclose(fp);
    fp = fopen("B.txt", "r");
    readMatrix(fp, b);
    fclose(fp);

    matrixAdd(a, b, c);
    printMatrix(c);

    return 0;
}