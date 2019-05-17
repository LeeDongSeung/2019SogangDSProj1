#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1024

typedef struct {
	int row, column, value;
}Term;

void readMatrix(FILE*fp,Term a[] );
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
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
void readMatrix(FILE*fp, Term a[]) {
	int n, m, tmp, count = 1;
	fscanf(fp,"%d %d", &n, &m);
	if (n > 20 || m > 20) {
		printf("size error\n");
		return 0;
	}
	a[0].row = n;
	a[0].column = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(fp,"%d", &tmp);
			if (tmp != 0) {
				a[count].row = i;
				a[count].column = j;
				a[count++].value = tmp;
			}
		}
	}
	a[0].value = --count;
}
void printMatrix(Term a[]) {
	int size = a[0].value;
	for (int i = 0; i <= size; i++) {
		printf("%d  %d  %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	int col = a[0].column;
	int counta = a[0].value;
	int countb = b[0].value;
	int indexa = 1, indexb = 1;
	int posa, posb,countc=1;
	posa = col*a[indexa].row + a[indexa].column;
	posb = col*b[indexb].row + b[indexb].column;
	while(indexa<=counta && indexb<=countb) {
		if (posa == posb) {
			int tmp = a[indexa].value + b[indexb].value;
			if (tmp != 0) {
				c[countc].row = a[indexa].row;
				c[countc].column = a[indexa].column;
				c[countc++].value = tmp;
			}
			indexa++;
			indexb++;
			posa = col*a[indexa].row + a[indexa].column;
			posb = col*b[indexb].row + b[indexb].column;
		}
		else if (posa < posb) {
			c[countc].row = a[indexa].row;
			c[countc].column = a[indexa].column;
			c[countc++].value = a[indexa].value;
			indexa++;
			posa = col*a[indexa].row + a[indexa].column;
		}
		else {
			c[countc].row = b[indexb].row;
			c[countc].column = b[indexb].column;
			c[countc++].value = b[indexb].value;
			indexb++;
			posb = col*b[indexb].row + b[indexb].column;
		}
	}
	for (; indexa <= counta; indexa++) {
		c[countc].row = a[indexa].row;
		c[countc].column = a[indexa].column;
		c[countc++].value = a[indexa].value;
	}
	for (; indexb <= countb; indexb++) {
		c[countc].row = b[indexb].row;
		c[countc].column = b[indexb].column;
		c[countc++].value = b[indexb].value;
	}
	c[0].value = --countc;
}