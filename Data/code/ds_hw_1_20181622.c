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
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE* fp, Term a[]) {
	int x;
	fscanf(fp, "%d", &a[0].row);
	fscanf(fp, "%d", &a[0].column);
	int k = 1;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &x);
			if (x != 0) {
				a[k].row = i;
				a[k].column = j;
				a[k].value = x;
				k++;
			}
		}
	}
	a[0].value = k-1;
}
void printMatrix(Term a[]) {
	for (int i = 0; i < a[0].value+1; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[],Term c[]) {
	int i = 0; int j = 0;
	int k = 1;
	c[0].column = a[0].column;
	c[0].row = a[0].row;
	c[k].value = 0;
	int ax = 1;
	int bx = 1;
	for (int i = 0; i < c[0].row; i++) {
		for (int j = 0; j < c[0].column; j++) {
			if (a[ax].row == i && a[ax].column == j) {
				c[k].value += a[ax].value;
				ax++;
			}
			if (b[bx].row == i && b[bx].column == j) {
				c[k].value += b[bx].value;
				bx++;
			}
			if (c[k].value != 0) {
				c[k].row = i;
				c[k].column = j;
				k++;
				c[k].value = 0;
			}			
		}
	}
	c[0].value = k-1;
}