#include <stdio.h>
#include<stdlib.h>
#define MAX_TERMS 1024

typedef struct {
	int col;
	int row;
	int value;
}Term;

void readMatrix(FILE* fp, Term target[]) {

	int row;
	int col;
	int value;

	fscanf(fp, "%d %d", &row, &col);

	target[0].col = col;
	target[0].row = row;
	target[0].value = 0;


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int res = fscanf(fp, "%d", &value);
			if (res == EOF) return;
			if (value != 0) {
				(target[0].value)++;
				target[target[0].value].col = j;
				target[target[0].value].row = i;
				target[target[0].value].value = value;
			}
		}
	}

	fclose(fp);

}

void matrixAdd(Term a[], Term b[], Term c[]) {

	int a_flag = 1;
	int b_flag = 1;
	c[0].value = 1;
	while (1) {

		if (a[a_flag].row > b[b_flag].row) {
			for (; a[a_flag].row != b[b_flag].row; b_flag++) {
				// b대입
				c[c[0].value].value = b[b_flag].value;
				c[c[0].value].row = b[b_flag].row;
				c[c[0].value].col = b[b_flag].col;
				c[0].value++;
			}

		}
		else if (a[a_flag].row < b[b_flag].row) {
			for (; a[a_flag].row != b[b_flag].row; a_flag++) {
				// a 대입
				c[c[0].value].value = a[a_flag].value;
				c[c[0].value].row = a[a_flag].row;
				c[c[0].value].col = a[a_flag].col;
				c[0].value++;
			}
		}
		else {

			if (a[a_flag].col == -1 && b[b_flag].col == -1)  break;
			// 끝난거 check 

			if (a[a_flag].col > b[b_flag].col) {
				//b대입
				c[c[0].value].value = b[b_flag].value;
				c[c[0].value].row = b[b_flag].row;
				c[c[0].value].col = b[b_flag].col;

				b_flag++;
			}
			else if (a[a_flag].col < b[b_flag].col) {
				//a 대입
				c[c[0].value].value = a[a_flag].value;
				c[c[0].value].row = a[a_flag].row;
				c[c[0].value].col = a[a_flag].col;

				a_flag++;
			}
			else {
				c[c[0].value].value = a[a_flag].value + b[b_flag].value;
				c[c[0].value].row = a[a_flag].row;
				c[c[0].value].col = a[a_flag].col;

				a_flag++;
				b_flag++;
			}

			c[0].value++;
		}
	}

	c[0].value--;
	return;
}

void printMatrix(Term target[]) {

	for (int i = 0; i <= target[0].value; i++) {
		printf("%d %d %d \n", target[i].row, target[i].col, target[i].value);
	}

}

int main() {

	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);


	c[0].col = a[0].col;
	c[0].row = a[0].row;
	c[0].value = 0;
	// c의 값 초기화

	a[a[0].value + 1].row = a[0].row;
	a[a[0].value + 1].col = -1;

	b[b[0].value + 1].row = b[0].row;
	b[b[0].value + 1].col = -1;
	// a 랑 b 경계 설정

	//for (int i = 0; i <= a[0].value; i++) {
	//	printf("%d %d %d \n", a[i].row, a[i].col, a[i].value);
	//}

	//printf("--------------\n");

	//for (int i = 0; i <= b[0].value; i++) {
	//	printf("%d %d %d \n", b[i].row, b[i].col, b[i].value);
	//}//test

	//printf("--------------\n");

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;

}