#include <stdio.h>
#include <Stdlib.h>

typedef struct {
	int row, col, value;
}Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term* a) {
	if (fp == NULL) {
		printf("FILE OPEN ERROR!!\n");
		return;
	}
	fscanf(fp, "%d %d", &a[0].row, &a[0].col);
	int temp, i=1;
	for (int j = 0; j < a[0].row; j++) {
		for (int k = 0; k < a[0].col; k++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0) {
				a[i].row = j;
				a[i].col = k;
				a[i++].value = temp;
			}
		}
	}
	a[0].value = i - 1;
}

void printMatrix(Term* a) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%3d %3d %4d\n", a[i].row, a[i].col, a[i].value);
}

void matrixAdd(Term* a, Term* b, Term* c) {
	if (a[0].row != b[0].row || a[0].col != b[0].col) {
		printf("Non additable matrix!!\n");
		return;
	}
	int VAL_A = a[0].value, VAL_B = b[0].value;
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	int i = 1, j = 1, n = 1;
	while (i <= VAL_A && j <= VAL_B) {
		if (a[i].row == b[j].row) {
			if (a[i].col == b[j].col) {
				c[n].row = a[i].row;
				c[n].col = a[i].col;
				c[n++].value = a[i++].value + b[j++].value;
			}
			else if (a[i].col < b[j].col) {
				c[n].row = a[i].row;
				c[n].col = a[i].col;
				c[n++].value = a[i++].value;
			}
			else {
				c[n].row = b[j].row;
				c[n].col = b[j].col;
				c[n++].value = b[j++].value;
			}
		}
		else if (a[i].row < b[j].row) {
			c[n].row = a[i].row;
			c[n].col = a[i].col;
			c[n++].value = a[i++].value;
		}
		else {
			c[n].row = b[j].row;
			c[n].col = b[j].col;
			c[n++].value = b[j++].value;
		}
	}
	if (i > VAL_A) {
		for (; j <= VAL_B; j++) {
			c[n].row = b[j].row;
			c[n].col = b[j].col;
			c[n++].value = b[j].value;
		}
	}
	else {
		for (; i <= VAL_A; i++) {
			c[n].row = a[i].row;
			c[n].col = a[i].col;
			c[n++].value = a[i].value;
		}
	}
	c[0].value = n - 1;
}

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp1 = fopen("A.txt", "r");
	readMatrix(fp1, a);
	fclose(fp1);

	FILE *fp2 = fopen("B.txt", "r");
	readMatrix(fp2, b);
	fclose(fp2);

	//printMatrix(a);
	//printMatrix(b);
	matrixAdd(a, b, c);
	printMatrix(c);
	system("PAUSE");
	return 0;
}