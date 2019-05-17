#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int value;
	int col;
	int row;
}term;
#define MAX 1024
void readmatrix(FILE* fp, term a[]);
void addmatrix(term a[], term b[], term c[]);
void printmatrix(term a[]);
int main() {
	term a[MAX]; term b[MAX]; term c[MAX];

	FILE* fp;
	errno_t err;

	err = fopen(&fp, "a[4].txt", "r");
	readmatrix(fp, a);
	fclose(fp);

	err = fopen(&fp, "b[3].txt", "r");
	readmatrix(fp, b);
	fclose(fp);

	addmatrix(a, b, c);

	printmatrix(c);

	return;

}

void readmatrix(FILE* fp, term a[]) {
	int row, col, temp;
	int count = 0;
	fscanf(fp, "%d %d", &row, &col);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0) {
				count++;
				a[count].value = temp;
				a[count].row = i;
				a[count].col = j;
			}
			if (feof(fp)) break;
		}
		if (feof(fp)) break;
	}
	a[0].row = row;
	a[0].col = col;
	a[0].value = count;
}

void addmatrix(term a[], term b[], term c[]) {
	int rowbegin = 0;
	int countA = 1, countB = 1, countC = 1;

	if (a[0].col != b[0].col && a[0].row != b[0].row) {
		puts("invalid addtion!");
		exit(-1);
	}

	c[0].col = a[0].col;
	c[0].row = a[0].row;

	while (1) {
		
		//��� ���� �ϳ��� ���� ����������� �ٸ� �Ѱ��� ��ĵ� ������ ����� while�� Ż��
		if (countA > a[0].value) {
			while (countB <= b[0].value) {
				c[countC].value = b[countB].value;
				c[countC].row = b[countB].row;
				c[countC++].col = b[countB++].col;
			}
			break;
		}

		else if (countB > b[0].value) {
			while (countA <= a[0].value) {
				c[countC].value = a[countA].value;
				c[countC].row = a[countA].row;
				c[countC++].col = a[countA++].col;
			}
			break;
		}

		//������ ��� ���� �ϳ��� �� ���� ���ϸ� ������ �Ѱ� ����� ������ ���� �����Ŀ� ����
		if (a[countA].row != rowbegin) {
			while (b[countB].row == rowbegin) {
				c[countC].value = b[countB].value;
				c[countC].row = b[countB].row;
				c[countC++].col = b[countB++].col;
			}
			rowbegin = b[countB].row;
		}
		else if (b[countB].row != rowbegin) {
			while (a[countA].row == rowbegin) {
				c[countC].value = a[countA].value;
				c[countC].row = a[countA].row;
				c[countC++].col = a[countA++].col;
			}
			rowbegin = a[countA].row;
		}
		//���� ���� ����ִ� ��쿡 ���� ����ó�� 
		if (a[countA].row != b[countB].row) {
			if (a[countA].row > b[countB].row) {
				while (a[countA].row != b[countB].row) {
					c[countC].row = b[countB].row;
					c[countC].col = b[countB].col;
					c[countC++].value = b[countB++].value;
				}
			}
			else if (a[countA].row < b[countB].row) {
				while (a[countA].row != b[countB].row) {
					c[countC].row = a[countA].row;
					c[countC].col = a[countA].col;
					c[countC++].value = a[countA++].value;
				}
			}
		}
		//���� ��Һ� �� �����Ŀ� �� ����
		if (a[countA].col > b[countB].col){
			c[countC].value = b[countB].value;
			c[countC].row = b[countB].row;
			c[countC++].col = b[countB++].col;
		}
		else if (a[countA].col < b[countB].col) {
			c[countC].value = a[countA].value;
			c[countC].row = a[countA].row;
			c[countC++].col = a[countA++].col;
		}
		else if (a[countA].col == b[countB].col) {
			c[countC].value = a[countA].value + b[countB].value;
			c[countC].row = a[countA].row;
			c[countC++].col = a[countA++].col;
			countB++;
		}
	}
	countC--;
	c[0].value = countC;
}

void printmatrix(term a[]) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
}