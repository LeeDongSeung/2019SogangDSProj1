#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]) {
	int n, m;
	fscanf(fp, "%d %d", &n, &m);
	int k = 1;
	a[0].row = n; a[0].column = m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int temp;
			fscanf(fp, "%d", &temp);
			if (!temp) continue;
			a[k].row = i;
			a[k].column = j;
			a[k++].value = temp;
		}
	a[0].value = --k;
}

void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[],Term b[],Term c[]){

	int i, j, k;

	for (i = 1, j = 1, k = 1; i <= a[0].value + 1 && j < b[0].value + 1; k++) {

		if (a[i].row < b[j].row) {
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				i++;
		}

		else if (a[i].row > b[j].row) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
		}
	
		else {
			if (a[i].column < b[j].column) {
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				i++;
			}

			else if (a[i].column > b[j].column) {
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = b[j].value;
				j++;
			}

			else {
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value + b[j].value;
				i++; j++;
			}
		}
	}
	
	for (; i <= a[0].value; i++, k++) {
		c[k].row = a[i].row;
		c[k].column = a[i].column;
		c[k].value = a[i].value;
	}
	for (; j <= b[0].value; j++, k++) {
		c[k].row = b[j].row;
		c[k].column = b[j].column;
		c[k].value = b[j].value;
	}
	k--;

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = k;
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