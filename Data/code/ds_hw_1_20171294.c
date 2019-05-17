#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]) {
	int n, m;
	int va, ro = 0, co = 0;
	fscanf(fp, "%d", &n);
	fscanf(fp, "%d", &m);
	a[0].row = n;
	a[0].column = m;
	for (int l = 1; l <= (n * m); l++) {
		fscanf(fp, "%d", &va);
		a[l].column = co;
		a[l].row = ro;
		a[l].value = va;
		co++;
		if ((l % m) == 0) { co = 0; ro++; }
	}
};
void printMatrix(Term a[]) {
	int n, m;
	n = a[0].row;
	m = a[0].column;

	for (int l = 0; l <= (n * m); l++) {
		if (a[l].value != 0) {
			printf("%d %d %d\n", a[l].row, a[l].column, a[l].value);
		}
	}
};
void matrixAdd(Term a[], Term b[], Term c[]) {
	int n, m, i = 0;
	n = a[0].row;
	m = a[0].column;
	c[0].row = n;
	c[0].column = m;
	for (int l = 1; l <= (n * m); l++) {
		c[l].column = a[l].column;
		c[l].row = a[l].row;
		c[l].value = a[l].value + b[l].value;
		if (c[l].value != 0) {
			i++;
		}
	}
	c[0].value = i;
};
int main() {
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