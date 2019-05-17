#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
}Term;

#define MAX_TERMS 1024
#define COMPARE(x,y) (x)<(y)?(-1):((x==y)?(0):(1))

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("A.txt", "r");
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
	if (fp == NULL) {
		fprintf(stderr, "input file error\n");
		exit(1);
	}
	int row, col,val,rows,cols, cnt=0;
	fscanf(fp, "%d %d",&rows,&cols);
	a[0].row = rows; a[0].column = cols;
	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++) {
			fscanf(fp, "%d", &val);
			if (val) {
				a[++cnt].row = row;
				a[cnt].column = col;
				a[cnt].value = val;
			}
		}
	}
	a[0].value = cnt;
}
void printMatrix(Term a[]) {
	int totalA = a[0].value;
	for (int i = 0; i <= totalA; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j, rows, cols, cnt, sum;
	int rows_a = a[0].row, rows_b = b[0].row;
	int cols_a = a[0].column, cols_b = b[0].column;
	int total_a = a[0].value, total_b = b[0].value;
	if (rows_a != rows_b || cols_a != cols_b) { //row�� column�� ���� �ٸ��� ���� �� ����
		fprintf(stderr, "Incompatible matrices\n");
		exit(1);
	}
	rows = rows_a; cols = cols_a; //���� ũ���� matrix�̴�, rows�� cols�� ����
	cnt = 0; // ������ term c�� ���� �� value ���� ���� ����. 0���� �ʱ�ȭ.
	// set boundary condition
	a[total_a + 1].row = rows; b[total_b + 1].row = rows; 
	i = 1, j = 1;
	while (i <= total_a && j <= total_b) {
		switch (COMPARE(a[i].row, b[j].row)) {
			case -1:
				for (; a[i].row < b[j].row; i++) {
					c[++cnt].row = a[i].row;
					c[cnt].column = a[i].column;
					c[cnt].value = a[i].value;
				}
				break;
			case 0:
				switch (COMPARE(a[i].column, b[j].column)) {
					case -1:
						//go to next term in a
						c[++cnt].row = a[i].row;
						c[cnt].column = a[i].column;
						c[cnt].value = a[i++].value;
						break;
					case 0:
						sum = a[i].value + b[j].value;
						if (sum) {
							c[++cnt].row = a[i].row;
							c[cnt].column = a[i].column;
							c[cnt].value = sum;
						}
						i++; j++;
						break;
					case 1:
						// go to next term in b
						c[++cnt].row = b[j].row;
						c[cnt].column = b[j].column;
						c[cnt].value = b[j++].value;
				}
				break;
			case 1:
				for (; b[j].row < a[i].row; j++) {
					c[++cnt].row = b[j].row;
					c[cnt].column = b[j].column;
					c[cnt].value = b[j].value;
				}
		}
	}
	// ���� �� �����ֱ�
	for (; i <= total_a; i++) {
		c[++cnt].row = a[i].row;
		c[cnt].column = a[i].column;
		c[cnt].value = a[i].value;
	}
	for (; j <= total_b; j++) {
		c[++cnt].row = b[j].row;
		c[cnt].column = b[j].column;
		c[cnt].value = b[j].value;
	}
	//c[0]�� row,column,value ���� �־��ֱ�
	c[0].row = rows; c[0].column = cols;
	c[0].value = cnt;
}


