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
	int row, column, count = 0, value;

	fscanf(fp, "%d %d", &row, &column);
	a[0].row = row; a[0].column = column;
	for (int j = 0;j < row;j++) {
		for (int i = 0;i < column;i++) {
			fscanf(fp, "%d", &value);
			if (value != 0) {
				count++;
				a[count].value = value;
				a[count].column = i;
				a[count].row = j;
			}
		}
	}
	a[count + 1].value = NULL;
	a[0].value = count;
}

void printMatrix(Term a[]) {
	for (int i = 0;i < MAX_TERMS;i++) {
		if (a[i].value == NULL)
			break;
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j, count = 0;
	i = 1; j = 1;
	
	c[count].row = a[0].row;
	c[count].column = a[0].column;
	count++;
	while (a[i].value != NULL &&  b[j].value != NULL) {
		if (a[i].row < b[j].row) {
			c[count].row = a[i].row;
			c[count].column = a[i].column;
			c[count].value = a[i].value;
			count++;i++;
		}
		else if (a[i].row == b[j].row) {
			if (a[i].column < b[j].column) {
				c[count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value;
				count++;i++;
			}
			else if (a[i].column == b[j].column) {
				c[count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value + b[j].value;
				count++;i++;j++;
			}
			else {
				c[count].row = b[j].row;
				c[count].column = b[j].column;
				c[count].value = b[j].value;
				count++;j++;
			}
		}

		else {
			c[count].row = b[j].row;
			c[count].column = b[j].column;
			c[count].value = b[j].value;
			count++;j++;
		}
	}
	while (a[i].value != NULL) {
		c[count].row = a[i].row;
		c[count].column = a[i].column;
		c[count].value = a[i].value;
		count++;i++;
	}
	while (b[j].value != NULL) {
		c[count].row = b[j].row;
		c[count].column = b[j].column;
		c[count].value = b[j].value;
		count++;j++;
	}
	c[0].value = count - 1;
	c[count].value = NULL;
}