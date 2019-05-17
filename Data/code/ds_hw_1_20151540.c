#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void) {
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
	int i, j, n, m;
	int tmp;
	int idx = 1;

	fscanf(fp, "%d %d", &n, &m);
	a[0].row = n;
	a[0].column = m;
	a[0].value = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fscanf(fp, "%d", &tmp);
			if (tmp != 0) {
				a[0].value++;
				a[idx].row = i;
				a[idx].column = j;
				a[idx++].value = tmp;
			}
		}
	}
	a[idx].row = NULL;
	a[idx].column = NULL;
	a[idx].value = NULL;
}

void printMatrix(Term a[]) {
	int i = 0;
	
	while (a[i].value != NULL) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
		i++;
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int aidx = 1, bidx = 1, cidx = 1;
	int colnum = a[0].column;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;
	while (a[aidx].value != NULL && b[bidx].value != NULL) {
		if (a[aidx].row * colnum + a[aidx].column == b[bidx].row * colnum + b[bidx].column) {
			c[cidx].row = a[aidx].row;
			c[cidx].column = a[aidx].column;
			c[cidx++].value = a[aidx++].value + b[bidx++].value;
			c[0].value++;
		}
		else if (a[aidx].row * colnum + a[aidx].column > b[bidx].row * colnum + b[bidx].column) {
			c[cidx].row = b[bidx].row;
			c[cidx].column = b[bidx].column;
			c[cidx++].value = b[bidx++].value;
			c[0].value++;
		}
		else {
			c[cidx].row = a[aidx].row;
			c[cidx].column = a[aidx].column;
			c[cidx++].value = a[aidx++].value;
			c[0].value++;
		}
	}
	if (a[aidx].value != NULL) {
		while (a[aidx].value != NULL) {
			c[cidx].row = a[aidx].row;
			c[cidx].column = a[aidx].column;
			c[cidx++].value = a[aidx++].value;
			c[0].value++;
		}
	}
	if (b[bidx].value != NULL) {
		while (a[aidx].value != NULL) {
			c[cidx].row = b[bidx].row;
			c[cidx].column = b[bidx].column;
			c[cidx++].value = b[bidx++].value;
			c[0].value++;
		}
	}
	c[cidx].row = NULL;
	c[cidx].column = NULL;
	c[cidx].value = NULL;
}