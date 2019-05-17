#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 1024
#include <stdio.h>

typedef struct {
	int row;
	int col;
	int value;
} matrix; // 명세서 상의 Term과 같음

int compare(int x, int y);
void readmatrix(FILE*, matrix*); // sparse matrix 입력 함수; fclose도 포함
void addmatrix(matrix*, matrix*, matrix*); // sparse matrix 두 개 입력 받아서 더한 값 리턴
void printMatirx(matrix []);


int main()
{
	FILE* fp;
	matrix A[MAX_SIZE], B[MAX_SIZE], D[MAX_SIZE];

	fp = fopen("A.txt", "r"); // A 읽기
	readmatrix(fp, A);

	fp = fopen("B.txt", "r"); // B 읽기
	readmatrix(fp, B);

	addmatrix(A, B, D);

	printMatirx(D);

	return 0;

}


int compare(int x, int y)
{
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

void readmatrix(FILE* fp, matrix* Mat)
{
	int count = 0;
	int row, col, temp;

	fscanf(fp, "%d %d", &row, &col);	// 첫 줄 읽기
	Mat[count].row = row;
	Mat[count].col = col;

	for (int i = 0; i < row; i++)	// 원소 읽기
		for (int j = 0; j < col; j++)
		{
			fscanf(fp, "%d", &temp);

			if (temp == 0) continue;
			count++;
			Mat[count].row = i;
			Mat[count].col = j;
			Mat[count].value = temp;
		}
	Mat[0].value = count;
	
	fclose(fp);

	return ;
}


void addmatrix(matrix* A, matrix* B, matrix* D)
{
	int i, j; // for loop에서 사용; i는 A의 index, j는 B의 index
	int rows_a = A[0].row, cols_a = A[0].col, totala = A[0].value;
	int rows_b = B[0].row, cols_b = B[0].col, totalb = B[0].value;
	int row = A[1].row;

	int count = 0;

	if (A[0].row != B[0].row || A[0].col != B[0].col) 
		printf("Cannot Add These matrices");
	else {


		for (i = 1, j = 1; i < totala || j < totalb; ) {
			if (A[i].row != row) {
				for (;B[j].row == row ; ) {
						D[++count].row = B[j].row; D[count].col = B[j].col;
						D[count].value = B[j++].value;
				}
					row = A[i].row;
				}

			else if (B[j].row != row) {
				for (; A[i].row == row; ) {
						D[++count].row = A[i].row; D[count].col = A[i].col;
						D[count].value = A[i++].value;
				}
				row = A[i].row;
			}

			else 
				switch (compare(A[i].col, B[j].col)) {
					case -1: /*go to next term in a*/
						D[++count].row = A[i].row; D[count].col = A[i].col;
						D[count].value = A[i++].value;
						break;
					case 0: /*add terms, go to next term in a and b*/
						D[++count].row = A[i].row; D[count].col = A[i].col;
						D[count].value = A[i++].value + B[j++].value;
						break;
					case 1: /*go to the next term in b*/
						D[++count].row = B[j].row; D[count].col = B[j].col;
						D[count].value = B[j++].value;
					
				}

		}
		D[0].row = rows_a; D[0].col = cols_b;
		D[0].value = count;
	}
	return ;
}

void printMatirx(matrix a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	return ;
}