#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
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
	int TR, TC, data;
	int i, j;

	fscanf(fp, "%d %d", &TR, &TC);
	a[0].row = TR; a[0].column = TC;
	a[0].value = 0;

	for (i = 0; i < TR; i++) {
		for (j = 0; j < TC; j++) {
			if (j == TC) fscanf(fp, "%d\n", &data);
			else fscanf(fp, "%d ", &data);
			if (data != 0) {
				a[0].value++;
				a[a[0].value].row = i;
				a[a[0].value].column = j;
				a[a[0].value].value = data;
			}
		}
	}
}
void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, k = 1;
	int t1 = a[0].value, t2 = b[0].value;
	c[0].row = a[0].row; c[0].column = a[0].column;
	//i = index for a
	//j = index for b
	//k = index for c
	while (i <= t1 && j <= t2) {
		if (b[j].row == a[i].row && b[j].column < a[i].column) { // compare column 1
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
		}
		else if (b[j].row == a[i].row && a[i].column < b[j].column) {// compare column 2
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
		}
		else if (b[j].row < a[i].row) { // row numbers are not equal (case1)
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
		}
		else if (a[i].row < b[i].row) { // row numbers are not equal (case2)
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
		}//
		//row equal
		else { //row equal, column equal
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value + b[j].value;
			i++;
			j++;
		}
		k++;
		//printf("i : %d   j : %d   k : %d   ", i, j, k);
	}
	//remaining

	while (i <= t1) {
		c[k].row = a[i].row;
		c[k].column = a[i].column;
		c[k].value = a[i].value;
		i++;
		k++;
	}
	while (j <= t2) {
		c[k].row = b[j].row;
		c[k].column = b[j].column;
		c[k].value = b[j].value;
		j++;
		k++;
	}
	c[0].value = k - 1;
}