#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[]);

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
	int n, m;
	fscanf(fp,"%d%d", &n, &m);
	int p = 1;
	a[0].row = n; a[0].column = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int t;
			fscanf(fp,"%d", &t);
			if (t == 0) continue;
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	a[0].value = p - 1;
}

void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int i=1, j=1, p=1;
	c[0].row = a[0].row;
	c[0].column = b[0].column;
	while (1) {
		if (j<=b[0].value&&(i > a[0].value || a[i].row > b[j].row || (a[i].row == b[j].row&&a[i].column > b[j].column))) {
			c[p].row = b[j].row;
			c[p].column = b[j].column;
			c[p++].value = b[j++].value;
		}
		else if (j <= b[0].value&&a[i].row == b[j].row&&a[i].column == b[j].column) {
			c[p].row = a[i].row;
			c[p].column = b[j].column;
			c[p++].value = a[i++].value + b[j++].value;
		}
		else {
			c[p].row = a[i].row;
			c[p].column = a[i].column;
			c[p++].value = a[i++].value;
		}
		if (i > a[0].value&&j > b[0].value)
			break;
	}
	c[0].value = p - 1;
}
