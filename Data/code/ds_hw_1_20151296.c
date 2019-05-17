#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
# define MAX_TERMS 1024

void readMatrix(FILE * fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int COMPARE(int a, int b) {
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}
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
	int n = 0, index = 1;

	fscanf(fp, "%d", &n);
	a[0].row = n;
	fscanf(fp, "%d", &n);
	a[0].column = n;

	for (int i = 0; i < (a[0].row * a[0].column); i++) {
		fscanf(fp, "%d", &n);
		if (n != 0) {
			a[index].row = i / a[0].column;
			a[index].column = i % a[0].column;
			a[index++].value = n;
		}
	}
	a[0].value = (--index);
}
void printMatrix(Term a[]) {
	for (int i = 0; i < a[0].value + 1; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, k = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	int na = a[0].value, nb = b[0].value;
	while (i <= na && j <= nb) {
		int x = COMPARE(a[i].row, b[j].row);
		int y = COMPARE(a[i].column, b[j].column);
		if (x == 1) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k++].value = b[j++].value;
		}
		else if (x == -1) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k++].value = a[i++].value;
		}
		else {
			if (y == 1) {
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k++].value = b[j++].value;
			}
			else if (y == -1) {
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k++].value = a[i++].value;
			}
			else {
				if ((a[i].value + b[j].value)) {
					c[k].row = a[i].row;
					c[k].column = a[i].column;
					c[k++].value = a[i].value + b[j].value;
				}
				i++; j++;
			}
		}
	}// while
	if (i != na + 1) {
		for (; i <= na; i++) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k++].value = a[i].value;
		}
	}
	if (j != nb + 1) {
		for (; j <= nb; j++) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k++].value = b[j].value;
		}
	}
	c[0].value = (--k);
}