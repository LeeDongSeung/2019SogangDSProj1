#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
}Term;

#define MAX_TERMS 1024
int compare(int a, int b) {
	if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	int cnt = 0, tmp=0;
	int index = 1;
	int i, j;
	
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	for (i = 0; i < a[0].row; i++) {
		for (j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &tmp);
			if (tmp != 0) {
				a[index].row = i;
				a[index].column = j;
				a[index++].value = tmp;
				cnt++;
			}
		}
	}
	a[0].value = cnt;
}

void printMatrix(Term a[]) {
	int i;
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value);
	for (i = 1; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {

	int i = 1, j = 1,k = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	while (i <= a[0].value && j <= b[0].value) {
		switch (compare(a[i].row, b[j].row)) {
			case 0: c[k].row = a[i].row;
					if (a[i].column == b[j].column) {
						c[k].column = a[i].column;
						c[k].value = a[i].value + b[j].value;
						k++; i++; j++;
					}
					else if (a[i].column < b[j].column) {
						c[k].column = a[i].column;
						c[k].value = a[i].value;
						k++; i++;
					}
					else {
						c[k].column = b[j].column;
						c[k].value = b[j].value;
						k++; j++;
					}break;
			case 1: c[k].row = b[j].row;
					c[k].column = b[j].column;
					c[k].value = b[j].value;
					k++; j++;
					break;
			case -1: c[k].row = a[i].row;
					 c[k].column = a[i].column;
					 c[k].value = a[i].value;
					 k++; i++;
		}

	}
	if (i > a[0].value) {
		for (; j <= b[0].value; j++, k++) {
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
		}
	}else if (j > b[0].value) {
		for (; i <= a[0].value; i++, k++) {
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
		}
	}
	c[0].value = k - 1;
	
}

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("A.txt", "r");
	if (fp == NULL) {
		printf("파일 읽기에 실패했습니다.\n");
		exit(1);
	}
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	if (fp == NULL) {
		printf("파일 읽기에 실패했습니다.\n");
		exit(1);
	}
	readMatrix(fp, b);
	fclose(fp);
	
	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}