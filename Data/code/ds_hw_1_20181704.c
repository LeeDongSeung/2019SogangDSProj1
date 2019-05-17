#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
    Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
    
    FILE *fp = fopen("A.txt", "r");
    readMatrix(fp ,a);
    fclose(fp);
    
    fp = fopen("B.txt", "r");
    readMatrix(fp, b);
    
    matrixAdd(a, b, c);
    printMatrix(c);
    return 0;
}
void readMatrix(FILE *fp, Term a[]) {
    int n, m;
    int count = 0;
    fscanf(fp, "%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            int t;
            count++;
            fscanf(fp, "%d", &t);
            
            a[count].column = i;
            a[count].row = j;
            a[count].value = t;
        }
    }
    a[0].column = n;
    a[0].row = m;
    a[0].value = n*m;
}
void matrixAdd(Term a[], Term b[], Term c[]) {
    int count=0;
    for(int i=1; i<=a[0].value; i++) {
        if(a[i].value != 0 || b[i].value != 0) {
            count++;
            c[count].column = a[i].column;
            c[count].row = a[i].row;
            c[count].value = a[i].value + b[i].value;
        }
    }
    c[0].column = a[0].column;
    c[0].row = a[0].row;
    c[0].value = count;
}
void printMatrix(Term a[]) {
    for(int i=0; i<=a[0].value; i++) {
        printf("%d %d %d\n", a[i].column, a[i].row, a[i].value);
    }
}

