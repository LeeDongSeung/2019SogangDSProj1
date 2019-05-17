#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1024

typedef struct Sparse_Matrix {
	int row;
	int col;
	int value;
}term;

void readMatrix(FILE* fp, term a[]) {
	int current = 1, count = 0;
	fscanf(fp, "%d %d", &(a[0].row), &(a[0].col));

	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			a[current].row = i;
			a[current].col = j;

			fscanf(fp, "%d", &(a[current].value));

			if (a[current].value != 0) {
				current++;
				count++;
			}
		}
	}
	a[0].value = count;
	return;
}

void matrixAdd(term a[], term b[], term c[]) {
	int i, j, row_num = a[0].row, col_num = a[0].col, term_num = a[0].value;
	int index_a = 1, index_b = 1;
	int k = 1;
	c[0].row = row_num;
	c[0].col = col_num;

	for (i = 0; i < row_num; i++) {
		for (j = 0; j < col_num; j++) {
			if (a[index_a].row == i && a[index_a].col == j) {
				if (b[index_b].row == i && b[index_b].col == j) {
					c[k].row = a[index_a].row;
					c[k].col = a[index_a].col;
					c[k].value = a[index_a].value + b[index_b].value;
					if (c[k].value == 0) {
						continue;
					}
					index_a++;
					index_b++;
					k++;
				}
				else {
					c[k].row = a[index_a].row;
					c[k].col = a[index_a].col;
					c[k].value = a[index_a].value;
					index_a++;
					k++;
				}
			}
			else
				if (b[index_b].row == i && b[index_b].col == j) {
					c[k].row = b[index_b].row;
					c[k].col = b[index_b].col;
					c[k].value = b[index_b].value;
					index_b++;
					k++;
				}
		}
	}
	c[0].value = k - 1;
}

void printMatrix(term a[]) {
	int i;
	printf("%d %d %d\n", a[0].row, a[0].col, a[0].value);
	for (i = 1; i <= a[0].value; i++) {
		if (a[i].value == 0) {
			continue;
		}
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	}
}
int main(void) {
	FILE* fp;
	term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}


