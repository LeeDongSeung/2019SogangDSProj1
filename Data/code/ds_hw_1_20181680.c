#define _CRT_SECURE_NO_WARNINGS
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
	int n, m;
	int p = 1;
	fscanf(fp, "%d%d", &n, &m);
	a[0].row = n;
	a[0].column = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int t;
			fscanf(fp, "%d", &t);
			if (t == 0) continue;
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	}
	a[0].value = p - 1;
}
void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, k = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	while (i <= a[0].value && j <= b[0].value) {
		if (a[i].row == b[j].row && a[i].column == b[j].column) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value + b[j].value;
			i++;
			j++;
			k++;
		}
		else if (a[i].row == b[j].row && a[i].column < b[j].column) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
			k++;
		}
		else if (a[i].row == b[j].row && a[i].column > b[j].column) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
			k++;
		}
		else if (a[i].row < b[j].row) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
			k++;
		}
		else if (a[i].row > b[j].row) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
			k++;
		}
	}
	if (a[0].value > b[0].value) {
		while (i <= a[0].value) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
			k++;
		}
	}
	else {
		while (j <= b[0].value) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
			k++;
		}
	}
	c[0].value = k - 1;
}