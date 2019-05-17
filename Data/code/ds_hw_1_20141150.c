#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, column, value;
} Term;

#define MAX_TERMS 1024

void readMatrix(FILE *fp, Term a[]) {
    int tmp_value = 0;
    int i = 1;
    int cnt = 0;
    if (fp != NULL) {
        fscanf(fp, "%d %d", &a[0].row, &a[0].column);
        while (!feof(fp)) {
            fscanf(fp, "%d", &tmp_value);
            if (tmp_value == 0) {
                cnt++;
                continue;
            }
            if ((cnt / a[0].column) >= a[0].row || (cnt % a[0].column) >= a[0].column) continue;
            a[i].value = tmp_value;
            a[i].row = cnt / a[0].column;
            a[i].column = cnt % a[0].column;
            i++;
            cnt++;
        }
    }
    a[0].value = i;
}

void printMatrix(Term a[]) {
    for (int i = 0; i <= a[0].value; i++) {
        printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
    }
}

void matrixAdd(Term a[], Term b[], Term c[]) {
    int a_index = 1;
    int b_index = 1;
    int c_index = 1;

    c[0].row = a[0].row;
    c[0].column = a[0].column;

    while (a_index < a[0].value && b_index < b[0].value) {
        int idx_a = a[a_index].row * a[0].column + a[a_index].column;
        int idx_b = b[b_index].row * b[0].column + b[b_index].column;
        if (idx_a < idx_b)
            c[c_index++] = a[a_index++];
        else if (idx_a == idx_b) {
            if ((a[a_index].value + b[b_index].value != 0)) {
                c[c_index].row = a[a_index].row;
                c[c_index].column = a[a_index].column;
                c[c_index++].value = a[a_index++].value + b[b_index++].value;
            } else {
                a_index++;
                b_index++;
            }
        } else {
            c[c_index++] = b[b_index++];
        }
    }

    for (; a_index < a[0].value;)
        c[c_index++] = a[a_index++];
    for (; b_index < b[0].value;)
        c[c_index++] = b[b_index++];
    c[0].value = c_index - 1;
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