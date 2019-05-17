#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 101

void readMatrix(FILE* fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[]);

int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("a.txt","r");
	readMatrix(fp,a);
	fclose(fp);
	
	fp = fopen("b.txt","r");
	readMatrix(fp,b);
	fclose(fp);
	
	matrixAdd(a,b,c);
	printMatrix(c);
	
	return 0;
}

void readMatrix(FILE* fp, Term a[]) { // 파일 내 행렬을 읽어들이는 함수 구현
	int k = 1, count = 0; // count는 행렬 내 요소들을 세는 변수이고, 구조체 행렬 a의 0번째 인덱스에는 파일 내 행렬의 row와 col만을 저장하므로 k=1로 지정하여 1번 인덱스부터 저장을 하고자 한다.
	fscanf(fp, "%d %d", &(a[0].row), &(a[0].column)); // 행과 열의 개수를 불러들인다.

	for (int i = 0; i < a[0].row; i++) { // 읽어들인 row의 갯수만큼 본 반복문을 반복
		for (int j = 0; j < a[0].column; j++) { //읽어들인 col의 갯수만큼 본 반복문을 반복
			a[k].row = i; // row값을 저장
			a[k].column = j; // col 값을 저장
			fscanf(fp, "%d", &(a[k].value)); //파일 내 행렬의 수를 읽어서 구조체 행렬 a의 k번째 항목에 저장. (value값에 해당 수를 저장한다.)

			k++; // 구조체 행렬 a에 값을 계속 채우기 위해 k를 증가시킨다.
		}
	}
	return;
}

void printMatrix(Term a[])
{
	int row_terms[101];
	int i, j, num_cols = a[0].column, num_terms = a[0].value, temp = 0, store = 0;
	
	Term c_transpose[101];
	
	c_transpose[0].column = a[0].row;
	c_transpose[0].row = num_cols;
	c_transpose[0].value = num_terms;
	
	if (num_terms > 0) {
		for (i = 0; i < num_cols; i++) row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) row_terms[a[i].column]++;
		temp = row_terms[1];
		row_terms[1] = 1 + row_terms[0];
		row_terms[0] = 1;
		for (i = 2; i < num_cols; i++) {
			store = row_terms[i];
			row_terms[i] = temp + row_terms[i - 1];
			temp = store;
		}
		for (i = 1; i <= num_terms; i++) {
			j = row_terms[a[i].column]++;
			c_transpose[j].row = a[i].column;
			c_transpose[j].column = a[i].row;
			c_transpose[j].value = a[i].value;
		}	

	}
	for (int k = 1; k <= c_transpose[0].value; k++) {
		if (c_transpose[k].value == 0)
			continue; // value값이 0이면 패스
		printf("%d %d %d\n", c_transpose[k].row, c_transpose[k].column, c_transpose[k].value); //value 값이 존재하면 출력
	}
	return;
}

void matrixAdd(Term a[],Term b[],Term c[])
{
	int k = 1;
	int cnt = 0;
	
	c[0].row = a[0].row;
	c[0].column = c[0].column;
	
	for (int i = 0; i < c[0].row; i++) { // 읽어들인 row의 갯수만큼 본 반복문을 반복
		for (int j = 0; j < c[0].column; j++) { //읽어들인 col의 갯수만큼 본 반복문을 반복
			c[k].row = i; // row값을 저장
			c[k].column = j; // col 값을 저장
			c[k].value = a[k].value + b[k].value; // 두 행렬의 같은 좌표 값을 합산하여 저장한다. 
			
			if (c[k].value != 0) // k번째 value 값이 0이 아닐 경우
				cnt++; // 0이 아닌 값의 개수를 체크하는 전역변수 c의 값을 1 증가시킨다.
			
			k++; // 구조체 행렬 a에 값을 계속 채우기 위해 k를 증가시킨다.
		}
	}
	c[0].value = cnt;
	return;
}
