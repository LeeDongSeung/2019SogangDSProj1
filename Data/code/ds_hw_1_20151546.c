#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("A.txt", "r");
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
	int i, j, temp, idx=1;
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	for (i = 0; i < a[0].row; ++i) {
		for (j = 0; j < a[0].column; ++j) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				a[idx].row = i;
				a[idx].column = j;
				a[idx++].value = temp;
			}
		}
	}
	a[0].value = idx - 1;
}

void printMatrix(Term a[]) {
	int i;
	for (i = 0; i <= a[0].value; ++i)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int c_a = 1, c_b = 1, c_c = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;

	while (c_a <= a[0].value && c_b <= b[0].value) {
		int idx_a = a[c_a].row * a[0].column + a[c_a].column;
		int idx_b = b[c_b].row * b[0].column + b[c_b].column;
		if (idx_a < idx_b) {
			c[c_c].row = a[c_a].row;
			c[c_c].column = a[c_a].column;
			c[c_c++].value = a[c_a++].value;
		}
		else if (idx_a == idx_b) {
			c[c_c].row = a[c_a].row;
			c[c_c].column = a[c_a].column;
			c[c_c++].value = a[c_a++].value + b[c_b++].value;
		}
		else {
			c[c_c].row = b[c_b].row;
			c[c_c].column = b[c_b].column;
			c[c_c++].value = b[c_b++].value;
		}
	}
	for (; c_a <= a[0].value; ++c_a) {
		c[c_c].row = a[c_a].row;
		c[c_c].column = a[c_a].column;
		c[c_c++].value = a[c_a].value;
	}
	for (; c_b <= b[0].value; ++c_b) {
		c[c_c].row = b[c_b].row;
		c[c_c].column = b[c_b].column;
		c[c_c++].value = b[c_b].value;
	}
	c[0].value = --c_c;
}