#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int compare(int, int); // compare �Լ�

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("a[4].txt", "r");

	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	
	return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	int i, j, count, nrow, ncol, value;
	nrow = a[0].row;
	ncol = a[0].column;
	for (i = 0, count = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			fscanf(fp, "%d", &value);
			if (value) {
				count++;
				a[count].row = i;
				a[count].column = j;
				a[count].value = value;
			}
		}
	}
	a[0].value = count;
}

void printMatrix(Term a[]) {
	int i;
	for (i = 0; i <= a[0].value; i++) {
		printf("%2d %2d %2d\n", a[i].row, a[i].column, a[i].value);
	}
}

int compare(int a, int b) {
	if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int rowsA, rowsB, valuesA, valuesB;
	int i, j, count, currentRowA, currentRowB;
	rowsA = a[0].row, rowsB = b[0].row;
	valuesA = a[0].value, valuesB = b[0].value;

	if (rowsA != rowsB && a[0].column != b[0].column) {
		printf("can't add different size matrices\n");
		exit(EXIT_FAILURE);
	}

	currentRowA = a[1].row, currentRowB = b[1].row;
	count = 0;
	for (i = 1, j = 1; i <= valuesA && j <= valuesB;) {
		/* A�� Row�� B�� Row�� ���� ���� ���(������ ũ�ų� ���� ���), ���� Row�� ��ü terms�� c�� �ֱ� */
		if (currentRowA != currentRowB) {
			if (currentRowA < currentRowB) {
				while (currentRowA == a[i].row) {
					c[++count].row = a[i].row;
					c[count].column = a[i].column;
					c[count].value = a[i].value;
					i++;
				}
				currentRowA = a[i].row;
			}
			else {
				while (currentRowB == b[j].row) {
					c[++count].row = b[j].row;
					c[count].column = b[j].column;
					c[count].value = b[j].value;
					j++;
				}
				currentRowB = b[j].row;
			}
		}
		/* ���� �� else if �� : a�� b �� �� ���� Row�� ���� ������ �� ������ ���� terms�� c�� ����*/
		else if (currentRowA != a[i].row) {
			while (currentRowB == b[j].row) {
				c[++count].row = b[j].row;
				c[count].column = b[j].column;
				c[count].value = b[j].value;
				j++;
			}
			currentRowB = b[j].row;
			currentRowA = a[i].row;
		}
		else if (currentRowB != b[j].row) {
			while (currentRowA == a[i].row) {
				c[++count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value;
				i++;
			}
			currentRowA = a[i].row;
			currentRowB = b[j].row;
		}
		/* a�� b�� currentRow�� ���� ���, column�� ���� ���ٸ� ���ؼ� c�� ����, column�� �۴ٸ� ���� ���� �ش� term�� c�� ���� */
		else {
			int sum;
			switch (compare(a[i].column, b[j].column)) {
			case 1:
				c[++count].row = b[j].row;
				c[count].column = b[j].column;
				c[count].value = b[j].value;
				j++;
				break;
			case 0:
				sum = a[i].value + b[j].value;
				if (sum) {
					c[++count].row = a[i].row;
					c[count].column = a[i].column;
					c[count].value = sum;
				}
				i++, j++;
				break;
			case -1:
				c[++count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value;
				i++;
			}
		}

	}

	/* outer for�� ���� ������ ��� ���� row terms�� ���� c�� ��� �־��ֱ� */
	while (a[i].row == currentRowA) {
		c[++count].row = a[i].row;
		c[count].column = a[i].column;
		c[count].value = a[i].value;
		i++;
	}

	while (b[j].row == currentRowB) {
		c[++count].row = b[j].row;
		c[count].column = b[j].column;
		c[count].value = b[j].value;
		j++;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = count;
}