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
void readMatrix(FILE *fp, Term a[]) {
	int row, col, tmp;
	int val = 0;
	fscanf(fp, "%d %d", &row, &col);
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%d", &tmp);
			if (tmp != 0) {
				a[++val].row = i;
				a[val].column = j;
				a[val].value = tmp;
			}
		}
	}
	a[0].row = row;
	a[0].column = col;
	a[0].value = val;
}
void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) 
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, val = 0, tmp;
	while (i <= a[0].value && j <= b[0].value) {
		if (a[i].row == b[j].row) {
			if (a[i].column < b[j].column) {
				c[++val].row = a[i].row;
				c[val].column = a[i].column;
				c[val].value = a[i].value;
				i++;
			}
			else if (a[i].column == b[j].column) {
				tmp = a[i].value + b[j].value;
				if (tmp != 0) {
					c[++val].row = a[i].row;
					c[val].column = a[j].column;
					c[val].value = tmp;
					i++; j++;
				}
			}
			else {
				c[++val].row = b[j].row;
				c[val].column = b[j].column;
				c[val].value = b[j].value;
				j++;
			}
		}
		else {
			if (a[i].row < b[j].row) {
				c[++val].row = a[i].row;
				c[val].column = a[i].column;
				c[val].value = a[i].value;
				i++;
			}
			else {
				c[++val].row = b[j].row;
				c[val].column = b[j].column;
				c[val].value = b[j].value;
				j++;
			}
		}
	}
	for (; i <= a[0].value; i++) {
		c[++val].row = a[i].row;
		c[val].column = a[i].column;
		c[val].value = a[i].value;
	}
	for (; j <= b[0].value; j++) {
		c[++val].row = b[j].row;
		c[val].column = b[j].column;
		c[val].value = b[j].value;
	}
	
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = val;
}