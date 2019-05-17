#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]) {
	int i = 1;
	int ro = 0, col = 0;

	if (fp == NULL) {
		printf("file error\n");
		return;
	}
	fscanf(fp, "%d", &a[0].row);
	fscanf(fp, "%d", &a[0].column);
	while (fscanf(fp, "%d", &a[i].value) != EOF) {
		if (a[i].value == 0) {
			col++;
			if (col > (a[0].column - 1)) {
				ro++;
				col = col - a[0].column;
			}
		}
		else {
			a[i].row = ro;
			a[i].column = col;
			col++;
			if (col > (a[0].column - 1)) {
				ro++;
				col = col - a[0].column;
			}
			i++;
		}
	}
	i--;
	a[0].value = i;
}
void printMatrix(Term a[]) {
	int i = 0;
	for(i; i <= a[0].value; i++){
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int fir = 1, sec = 1, thi = 1;

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	while (fir <= a[0].value && sec <= b[0].value) {
		if (8 * a[fir].row + a[fir].column == 8 * b[sec].row + b[sec].column) {
			c[thi].value = a[fir].value + b[sec].value;
			c[thi].row = a[fir].row;
			c[thi].column = a[fir].column;
			fir++;
			sec++;
			thi++;
		}
		else if (8 * a[fir].row + a[fir].column > 8 * b[sec].row + b[sec].column) {
			c[thi].value = b[sec].value;
			c[thi].row = b[sec].row;
			c[thi].column = b[sec].column;
			sec++;
			thi++;
		}
		else {
			c[thi].value = a[fir].value;
			c[thi].row = a[fir].row;
			c[thi].column = a[fir].column;
			fir++;
			thi++;
		}
	}
	while (sec <= b[0].value) {
		c[thi].value = b[sec].value;
		c[thi].row = b[sec].row;
		c[thi].column = b[sec].column;
		sec++;
		thi++;
	}
	while (fir <= a[0].value) {
		c[thi].value = a[fir].value;
		c[thi].row = a[fir].row;
		c[thi].column = a[fir].column;
		fir++;
		thi++;
	}

	c[0].value = thi - 1;
}
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	FILE *ab = fopen("b[3].txt", "r");
	readMatrix(ab, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;

}