#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

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

void readMatrix(FILE *fp, Term a[]) {
	
	fscanf(fp, "%d %d", &(a[0].row), &(a[0].column));
	
	int i = 0, k = 1, x;
	while ( EOF != fscanf(fp, "%d", &x) ){

		if (x != 0) {
			a[k].row = i / (a[0].column);
			a[k].column = i % (a[0].column);
			a[k].value = x;

			k++;
		}

		i++;
	}
	a[0].value = k - 1;
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	int adex = 1, bdex = 1, k = 1, sum;
	int aflag = 0, bflag = 0;
	int s1, s2;
	while (1) {
		if (a[adex].row > b[bdex].row) s1 = 1;
		else if (a[adex].row == b[bdex].row) s1 = 0;
		else s1 = -1;

		if (aflag == 1) s1 = 1;
		if (bflag == 1) s1 = -1;

		switch (s1) {

		case 1: {
			c[k].row = b[bdex].row;
			c[k].column = b[bdex].column;
			c[k].value = b[bdex].value;
			bdex++, k++;
			break;
		}

		case 0: {
			if (a[adex].column > b[bdex].column) s2 = 1;
			else if (a[adex].column == b[bdex].column) s2 = 0;
			else s2 = -1;

			switch (s2) {

			case 1: {
				c[k].row = b[bdex].row;
				c[k].column = b[bdex].column;
				c[k].value = b[bdex].value;
				bdex++, k++;
				break;
			}
			case 0: {
				sum = a[adex].value + b[bdex].value;
				if (sum != 0) {
					c[k].row = a[adex].row;
					c[k].column = a[adex].column;
					c[k].value = sum;
					adex++, bdex++, k++;
					break;
				}
			}

			case -1: {
				c[k].row = a[adex].row;
				c[k].column = a[adex].column;
				c[k].value = a[adex].value;
				adex++, k++;
				break;
			}

			}
			break;
		} 

		case -1: {
			c[k].row = a[adex].row;
			c[k].column = a[adex].column;
			c[k].value = a[adex].value;
			adex++, k++;
			break;
		}

		}

		//각 Term의 end flag
		if (adex > a[0].value) aflag = 1;
		if (bdex > b[0].value) bflag = 1;

		//break 조건
		if ((aflag == 1) && (bflag == 1)) break;

	}
	c[0].value = --k;
}

void printMatrix(Term a[]) {
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value);

	for (int i = 1; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}