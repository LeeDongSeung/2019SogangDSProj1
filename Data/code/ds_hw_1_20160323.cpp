#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1024

typedef struct {
	int row, column, value;
}Term;

void readMatrix(FILE* fp, Term a[]){
	int i, j, value = 0, count = 0;
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	for (i = 0; i < a[0].row; i++) {
		for (j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &value);
			if(value) { 
				a[++count].row = i;
				a[count].column = j;
				a[count].value = value;
			}
		}
	}
	a[0].value = count;

	return;
}

void printMatrix(Term a[]) {
	int i;
	for (i = 0; i <= a[0].value; i++) {
		printf("%d %d %d", a[i].row, a[i].column, a[i].value);
		if (i != a[0].value) printf("\n");
	}
	return;
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j, k = 0;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	if (a[0].row != b[0].row || a[0].column != b[0].column) {
		printf("Cannot add two matrices that are not the same size.\n");
		return;
	}
	for (i = 1, j= 1; i <= a[0].value && j<=b[0].value; ) {
		if (a[i].row == b[j].row && a[i].column == b[j].column) {
			c[++k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i++].value + b[j++].value;
		}
		else if (a[i].row == b[j].row && a[i].column < b[j].column) {
			c[++k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i++].value;
		}
		else if (a[i].row == b[j].row && a[i].column > b[j].column) {
			c[++k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j++].value;
		}
		else if (a[i].row < b[j].row) {
			c[++k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i++].value;
		}
		else if (a[i].row > b[j].row) {
			c[++k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j++].value;
		}
	}
	if (a[0].value < b[0].value) {
		for (; j <= b[0].value;) {
			c[++k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j++].value;
		}
	}
	else {
		for (; i <= a[0].value; ) {
			c[++k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i++].value;
		}
	}
	c[0].value = k;
	
	return;
}

int main()
{
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