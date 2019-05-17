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

	fscanf(fp, "%d %d", &a[0].row, &a[0].column);

	int row, col, value, total;
	total = 0;

	for (row = 0; row < a[0].row; row++) {
		col = 0;
		for (col = 0; col < a[0].column; col++) {
			if (col != a[0].column - 1)
				fscanf(fp, "%d ", &value);
			else
				fscanf(fp, "%d\n", &value);
			if (value != 0) {
				total++;
				a[total].row = row;
				a[total].column = col;
				a[total].value = value;
			}
		}
	}

	a[0].value = total;

	return;

}



void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);

	return;

}



void matrixAdd(Term a[], Term b[], Term c[]) {
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	int starta = 1;
	int startb = 1;
	int finisha = a[0].value;
	int finishb = b[0].value;
	int total = 1;

	while (starta <= finisha && startb <= finishb) {
		if (a[starta].row < b[startb].row) {
			c[total].row = a[starta].row;
			c[total].column = a[starta].column;
			c[total].value = a[starta].value;
			starta++;
		}
		else if (a[starta].row > b[startb].row) {
			c[total].row = b[startb].row;
			c[total].column = b[startb].column;
			c[total].value = b[startb].value;
			startb++;
		}
		else {
			if (a[starta].column < b[startb].column) {
				c[total].row = a[starta].row;
				c[total].column = a[starta].column;
				c[total].value = a[starta].value;
				starta++;
			}
			else if (a[starta].column > b[startb].column) {
				c[total].row = b[startb].row;
				c[total].column = b[startb].column;
				c[total].value = b[startb].value;
				startb++;
			}
			else {
				c[total].row = a[starta].row;
				c[total].column = a[starta].column;
				c[total].value = a[starta].value + b[startb].value;
				starta++;
				startb++;
			}
		}
		total++;
	}
	if ((starta == finisha) && (startb == finishb))
		return;
	if (starta == finisha) {
		while (startb <= finishb) {
			c[total].row = b[startb].row;
			c[total].column = b[startb].column;
			c[total].value = b[startb].value;
			total++;
			startb++;
		}
	}
	else {
		while (starta <= finisha) {
			c[total].row = a[starta].row;
			c[total].column = a[starta].column;
			c[total].value = a[starta].value;
			total++;
			starta++;
		}
	}

	c[0].value = total - 1;
	return;
}