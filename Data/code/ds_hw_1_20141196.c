#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TEMRS 1024
#define COMPARE(x,y) ( (x == y) ? 0 : ( (x > y) ? 1 : -1 ) )

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void) {
	Term a[MAX_TEMRS], b[MAX_TEMRS], c[MAX_TEMRS];
	FILE *fp;
	
	fopen(&fp, "A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fopen(&fp, "B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	int data, i = 0, row = 0, col = 0, rows, cols;
	
	if (fscanf(fp, "%d %d", &rows, &cols) == EOF) {
		printf("file open error\n");
		return;
	}

	a[0].row = rows; a[0].column = cols;
	
	while (fscanf(fp, "%d", &data) != EOF) {
		if (data) {
			a[++i].value = data;
			a[i].row = row;
			a[i].column = col;
		}
		col++;
		if (col == cols) {
			col = 0;
			row++;
		}
	}
	a[0].value = i;
}
void printMatrix(Term a[]) {
	int vals = a->value;

	for (int i = 0; i <= vals; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, val = 0;
	int aval = a->value, bval = b->value;

	if (a[0].row != b[0].row || a[0].column != b[0].column) {
		printf("row column�� ���� �ٸ��ϴ�.\n");
		return;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;


	while (i <= aval && j <= bval) {
		switch (COMPARE(a[i].row, b[j].row)) { 
		case 0:// row ����
			switch (COMPARE(a[i].column, b[j].column)) {
			case 0: // row, col �Ѵ� ����
				c[++val].row = a[i].row;
				c[val].column = a[i].column;
				c[val].value = a[i++].value + b[j++].value;
				break;
			case -1: 
				c[++val].row = a[i].row;
				c[val].column = a[i].column;
				c[val].value = a[i++].value;
				break;
			case 1:
				c[++val].row = b[j].row;
				c[val].column = b[j].column;
				c[val].value = b[j++].value;
				break;
			}
			break;
		//row�ٸ�
		case -1:
			c[++val].row = a[i].row;
			c[val].column = a[i].column;
			c[val].value = a[i++].value;
			break;
		case 1:
			c[++val].row = b[j].row; 
			c[val].column = b[j].column;
			c[val].value = b[j++].value;
			break;
		}
	}

	while (i <= aval) {
		c[++val].row = a[i].row;
		c[val].column = a[i].column;
		c[val].value = a[i++].value;
	}
	while (j <= bval) {
		c[++val].row = b[j].row;
		c[val].column = b[j].column;
		c[val].value = b[j++].value;
	}

	c[0].value = val;
}
