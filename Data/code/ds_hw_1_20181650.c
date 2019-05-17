#include <stdio.h>
#include <stdlib.h>

int max_row, max_col, count = 0;

typedef struct {
	int row, column, value;
}Term;

#define MAX_TERMS 1024

void readMatrix(FILE *fp, Term a[]);
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

void readMatrix(FILE *fp,Term a[]) {
	int index = 0;
	fscanf(fp,"%d %d ", &max_row, &max_col);

	for (int i = 0; i < max_row; i++) {
		for (int j = 0; j < max_col; j++) {
			a[index].row = i;
			a[index].column = j;
			fscanf(fp,"%d ", &a[index].value);
			index++;
		}
	}
	
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int index = 0;

	for (int i = 0; i < max_row; i++) {
		for (int j = 0; j < max_col; j++) {
			c[index].row = i;
			c[index].column = j;
			c[index].value = a[index].value + b[index].value;

			if (c[index].value == 0)
				count++;
			index++;
		}
	}
}

void printMatrix(Term a[]) {
	int index = 0;

	printf("%d %d %d\n", max_row, max_col, max_row*max_col-count);

	for (int i = 0; i < max_row; i++) {
		for (int j = 0; j < max_col; j++) {

			if (a[index].value == 0) {
				index++;
				continue;
			}

			printf("%d %d %d\n", i, j, a[index].value);
			index++;
		}
	}
}