#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 401
#define MAX_COL 20
#define MAX_ROW 20

typedef struct {
	int row;
	int column;
	int value;
} Term;

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

	int i = 1, j = 0, k = 0;
	int maxrow, maxcol, cnt = 0;

	fscanf(fp, "%d %d", &maxrow, &maxcol);
	while (fscanf(fp, "%d", &a[i].value) != EOF) {
			a[i].row = j;
			a[i].column = k;
			k++; i++;
			if (k == maxcol) {
				j++;
				k = 0;
			}
		}
	
	a[0].row = maxrow;
	a[0].column = maxcol;
	a[0].value = 0;
}

void printMatrix(Term a[]) {

	int i;

	for (i = 0; i < (a[0].row)*(a[0].column)+1; i++) {
		
		if (a[i].value != 0) {
			printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
		}
	
	}

}

void matrixAdd(Term a[], Term b[], Term c[]) {

	int i;
	int cnt = 0;

	for (i = 1; i < (a[0].row)*(a[0].column)+1; i++) {
		c[i].row = a[i].row;
		c[i].column = a[i].column;
		c[i].value = a[i].value + b[i].value;

		if (c[i].value != 0) {
			cnt++;
		}
	}

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = cnt;

}




