#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int row, column, value;
}Term;
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
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	int rw=0, col=0, i, j, check=0, num=1, res=0;
	res=fscanf(fp,"%d %d", &rw, &col);
	if (res == EOF) {
		a[0].row = 0;
		a[0].column = 0;
		a[0].value = 0;
		return;
	}
	a[0].row = rw;
	a[0].column = col;
	for (i = 0; i < rw; i++) {
		for (j = 0; j < col; j++) {
			fscanf(fp,"%d", &check);
			if (check == 0)continue;
			else {
				a[num].row = i;
				a[num].column = j;
				a[num].value = check;
				num++;
			}
		}
	}
	a[0].value = num-1;
}
void printMatrix(Term a[]) {
	int rw, col, num;
	num = a[0].value;
	int i = 0;
	for (i = 0; i <= num; i++) {
		printf("%-2d %-2d %-2d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1, j = 1, n = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	while (i <= a[0].value&&j <= b[0].value) {
		if (a[i].row == b[j].row) {
			if (a[i].column == b[j].column) {
				if (a[i].value + b[j].value != 0) {
					c[n].row = a[i].row;
					c[n].column = a[i].column;
					c[n].value = a[i].value + b[j].value;
					i++; j++; n++; 
				}
				else {
					i++; j++;
				}
			}
			else if (a[i].column < b[j].column) {
				c[n].row = a[i].row;
				c[n].column = a[i].column;
				c[n].value = a[i].value;
				i++; n++;
			}
			else {
				c[n].row = b[j].row;
				c[n].column = b[j].column;
				c[n].value = b[j].value;
				j++; n++;
			}
		}
		else if (a[i].row<b[j].row) {
			c[n].row = a[i].row;
			c[n].column = a[i].column;
			c[n].value = a[i].value;
			i++; n++;
		}
		else {
			c[n].row = b[j].row;
			c[n].column = b[j].column;
			c[n].value = b[j].value;
			j++; n++;
		}
	}
	for (;i <= a[0].value;) {
		c[n].row = a[i].row;
		c[n].column = a[i].column;
		c[n].value = a[i].value;
		i++; n++;
	}
	for (;j <= b[0].value;) {
		c[n].row = b[j].row;
		c[n].column = b[j].column;
		c[n].value = b[j].value;
		j++; n++;
	}
	c[0].value = n-1;
}