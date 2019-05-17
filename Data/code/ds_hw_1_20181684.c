#define _CRT_SECURE_NO_WARNINGS
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

	FILE *fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}

void readMatrix(FILE* fp, Term a[])
{
	int i, j, t = 1;
	a[0].value = 0;
	fscanf(fp, "%d %d", &a[0].column, &a[0].row);
	for (i = 0; i < a[0].column; i++) {
		for (j = 0; j < a[0].row; j++) {
			fscanf(fp, "%d", &a[t].value);
			a[t].column = i;
			a[t].row = j;
			a[0].value += 1;
			t++;
		}
	}
}

void printMatrix(Term a[])
{
	int i;
	for (i = 0; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].column, a[i].row, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int i;
	int temp = 1;
	c[0].column = a[0].column; c[0].row = a[0].row;
	c[0].value = 0;
	for (i = 1; i <= c[0].column * c[0].row; i++) {
		if (a[i].value + b[i].value != 0) {
			c[0].value++; c[temp].value = a[i].value + b[i].value;
			c[temp].column = b[i].column; c[temp].row = b[i].row;
			temp++;
		}

	}
}