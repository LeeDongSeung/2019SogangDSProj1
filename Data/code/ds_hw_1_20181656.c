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
	int n, m, val, num=1;

	fscanf(fp, "%d %d\n", &n, &m);
	a[0].row = n;
	a[0].column = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(fp, "%d", &val);
			a[num].row = i;
			a[num].column = j;
			a[num].value = val;
			num++;

			if (j == m - 1)
				fscanf(fp, "\n");
			else
				fscanf(fp, " ");
		}
	}
}

void printMatrix(Term a[]) {
	int n, m, total, i=1;
	n = a[0].row;
	m = a[0].column;
	total = n * m;

	printf("%d %d %d\n", n, m, a[0].value);
	for(int j=1; j<total+1; j++)
		printf("%d %d %d\n", a[j].row, a[j].column, a[j].value);
	
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int n, m, total, val=0;

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	
	n = a[0].row;
	m = a[0].column;
	total = n * m;

	for (int i = 1; i < total + 1; i++) {
		c[i].row = a[i].row;
		c[i].column = a[i].column;
		c[i].value = a[i].value + b[i].value;

		if (c[i].value)
			val++;
	}
	c[0].value = val;
}