#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
#define MAX_TERMS 1024
typedef struct {
	int col;
	int row;
	int value;
}term;
void readMatrix(FILE *fp, term a[]);
void printMatrix(term a[]);
void matrixAdd(term a[], term b[], term c[]);

int main(void)
{
	term aa[MAX_TERMS];
	term bb[MAX_TERMS];
	term cc[MAX_TERMS];

	FILE *fpa = fopen("a[4].txt", "r");
	if (fpa == NULL) {
		printf("파일 열기 실패");
		exit(1);
	}
	int fia;
	readMatrix(fpa, aa);
	fia = fclose(fpa);
	if (fia == EOF) {
		printf("파일 닫기 실패");
		exit(1);
	}

	FILE *fpb = fopen("b[3].txt", "r");
	if (fpb == NULL) {
		printf("파일 열기 실패");
		exit(1);
	}
	int fib;
	readMatrix(fpb, bb);
	fib = fclose(fpb);
	if (fib == EOF) {
		printf("파일 닫기 실패");
		exit(1);
	}

	matrixAdd(aa, bb, cc);
	printMatrix(cc);

	return 0;
}

void readMatrix(FILE *fp, term a[])
{
	int n, m, i, t = 0;
	fscanf(fp, "%d %d", &n, &m);
	a[0].row = n;
	a[0].col = m;
	for (i = 1; i < MAX_TERMS; i++) {
		if (feof(fp) != 0)
			break;
		fscanf(fp, "%d", &a[i].value);
		a[i].row = t / m;
		a[i].col = t % m;
		t++;
		if (a[i].value == 0)
			i--;
	}
	a[0].value = i - 1;
}

void printMatrix(term a[])
{
	int i;
	i = a[0].value;
	if (a[i].value != 0)
		for (int j = 0; j <= i; j++)
			printf("%d %d %d\n", a[j].row, a[j].col, a[j].value);
	else
		for (int j = 0; j < i; j++)
			printf("%d %d %d\n", a[j].row, a[j].col, a[j].value);
}

void matrixAdd(term a[], term b[], term c[])
{
	if ((a[0].row != b[0].row) || (a[0].col != b[0].col))
		printf("Error : row or column not equal each other");
	else {
		int i = 1, j = 1, n = 1;
		c[0].row = a[0].row;
		c[0].col = a[0].col;
		for (; (i <= a[0].value) && (j <= b[0].value); n++) {
			if (a[i].row == b[j].row)
				if (a[i].col == b[j].col) {
					if (a[i].value + b[j].value) {
						c[n].row = a[i].row;
						c[n].col = a[i].col;
						c[n].value = a[i].value + b[j].value;
						i++;
						j++;
					}
					else {
						i++;
						j++;
					}
				}
				else if (a[i].col < b[j].col) {
					c[n].row = a[i].row;
					c[n].col = a[i].col;
					c[n].value = a[i].value;
					i++;
				}
				else {
					c[n].row = b[j].row;
					c[n].col = b[j].col;
					c[n].value = b[j].value;
					j++;
				}
			else if (a[i].row < b[j].row) {
				c[n].row = a[i].row;
				c[n].col = a[i].col;
				c[n].value = a[i].value;
				i++;
			}
			else {
				c[n].row = b[j].row;
				c[n].col = b[j].col;
				c[n].value = b[j].value;
				j++;
			}
		}
		for (; i <= a[0].value; n++) {
			c[n].row = a[i].row;
			c[n].col = a[i].col;
			c[n].value = a[i].value;
			i++;
		}
		for (; j <= b[0].value; n++) {
			c[n].row = b[j].row;
			c[n].col = b[j].col;
			c[n].value = b[j].value;
			j++;
		}
		c[0].value = n - 2;
	}
}
