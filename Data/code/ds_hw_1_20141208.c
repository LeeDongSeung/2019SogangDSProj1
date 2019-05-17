#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, col, value;
} Term;
#define MAX_TERMS 1024
#define COMPARE(x,y) (x>y)?-1:(x<y)?0:1
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE* fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	matrixAdd(b, a, c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE* fp, Term a[]) {
	fscanf(fp, "%d", &a[0].row);
	fscanf(fp, "%d", &a[0].col);
	int count, temp;
	count = 0;
	for (int i = 1; i <= a[0].row * a[0].col; i++) {

		fscanf(fp, "%d", &temp);
		if (temp == 0) continue;
		else {
			count++;
			if (i % a[0].col == 0) { //마지막 열인 경우
				a[count].row = i / a[0].col - 1;
				a[count].col = a[0].col - 1;

			}
			else {
				a[count].row = i / a[0].col;
				a[count].col = i % a[0].col - 1;
			}
			a[count].value = temp;
		}
	}
	a[0].value = count;
}

void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) {
		printf("%d  %d  %d\n", a[i].row, a[i].col, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j = 1, row, count = 0;
	if (a[0].value < b[0].value) {
		int temp;
		temp = a;
		a = b;
		b = temp;
	}
	for (i = 1; i <= a[0].value;) {
		row = a[i].row;
		for (; j <= b[0].value;) {
			switch (COMPARE(b[j].row, row)) {
			case -1: //b[j].row > row
				for (; a[i].row < b[j].row; i++) {
					count++;
					c[count].row = a[i].row;
					c[count].col = a[i].col;
					c[count].value = a[i].value;
				}
				break;
			case 0: //b[j].row < row
				for (; b[j].row < row; j++) {
					count++;
					c[count].row = b[j].row;
					c[count].col = b[j].col;
					c[count].value = b[j].value;
				}
				break;
			case 1: //b[j].row = row
				for (; b[j].row == row && a[i].row == row;) {
					switch (COMPARE(b[j].col, a[i].col)) {
					case -1: //b[j].col > a[i].col
						count++;
						c[count].row = a[i].row;
						c[count].col = a[i].col;
						c[count].value = a[i].value;
						i++;
						break;
					case 0: //b[j].col < a[i].col
						count++;
						c[count].row = b[j].row;
						c[count].col = b[j].col;
						c[count].value = b[j].value;
						j++;
						break;
					case 1: //b[j].col = a[i].col
						count++;
						c[count].row = a[i].row;
						c[count].col = a[i].col;
						c[count].value = a[i].value + b[j].value;
						i++;
						j++;
						break;
					}
				}
			}
			if (a[i].row != row) break;


		}
		if (j > b[0].value) {
			count++;
			c[count].row = a[i].row;
			c[count].col = a[i].col;
			c[count].value = a[i].value;
			i++;
		}
	}
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	c[0].value = count;
}