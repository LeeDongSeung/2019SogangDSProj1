#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row;
	int column;
	int value;
}Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main()
{
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

void readMatrix(FILE* fp, Term a[])
{
	fscanf(fp, "%d %d", &a[0].row , &a[0].column);
	
	int row = a[0].row;
	int col = a[0].column;

	int idx = 1;

	for(int i=0; i<row; i++)
		for (int j = 0; j < col; j++)
		{
			fscanf(fp, "%d", &a[idx].value);
			if (a[idx].value == 0)
				continue;

			a[idx].row = i;
			a[idx].column = j;
			idx++;
		}

	a[0].value = --idx; // idx 가 1증가 된 상태이므로 -1 을 해준다.

}

void printMatrix(Term a[])
{
	for (int k = 0; k<=a[0].value ; k++)
		printf("%d %d %d \n", a[k].row, a[k].column, a[k].value);
	
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	int a_idx = 1; // a 배열의 인덱스 값
	int b_idx = 1; // b 배열의 인덱스 값
	int c_idx = 1; // c 배열의 인덱스 값

	int flag = 1;

	while (1)
	{
		if (a[a_idx].row == b[b_idx].row) // 조건문 1 : a의 행과 b의 행이 같을 때
		{
			if (a[a_idx].column == b[b_idx].column) // 조건문 1-a : a의 열과 b의 열도 같을 때
			{
				c[c_idx].row = a[a_idx].row;
				c[c_idx].column = a[a_idx].column;
				c[c_idx].value = a[a_idx].value + b[b_idx].value;
				c_idx++;
				a_idx++;
				b_idx++;

			}

			else if (a[a_idx].column < b[b_idx].column) // 조건문 1-b : a의 열 < b의 열
			{
				c[c_idx].row = a[a_idx].row;
				c[c_idx].column = a[a_idx].column;
				c[c_idx].value = a[a_idx].value;
				a_idx++;
				c_idx++;

			}

			else // 조건문 1-c : a의 열 > b의 열
			{
				c[c_idx].row = b[b_idx].row;
				c[c_idx].column = b[b_idx].column;
				c[c_idx].value = b[b_idx].value;
				b_idx++;
				c_idx++;
			}
		}

		else if (a[a_idx].row < b[b_idx].row) // 조건문 2 : a의 행 < b의 행
		{
			c[c_idx].row = a[a_idx].row;
			c[c_idx].column = a[a_idx].column;
			c[c_idx].value = a[a_idx].value;
			a_idx++;
			c_idx++;
		}

		else // 조건문 3 : a의 행 > b의 행
		{
			c[c_idx].row = b[b_idx].row;
			c[c_idx].column = b[b_idx].column;
			c[c_idx].value = b[b_idx].value;
			b_idx++;
			c_idx++;
		}


		if (a_idx - 1 == a[0].value) // 탈출조건 1 : (a의 인덱스 값 - 1) 이 a 희소행렬의 원소의 갯수와 같아질 때 탈출
			{
				flag = 0;
				--a_idx;
				break;
			}

		if (b_idx -1  == b[0].value) // 탈출조건 2 : (b의 인덱스 값 - 1) 이 b 희소행렬의 원소의 갯수와 같아질 때 탈출
			{
				flag = 1;
				--b_idx;
				break;
			}

	}


	if (flag == 0) // 남아있는 b 처리
	{
		while (b_idx <= b[0].value)
		{
			c[c_idx].row = b[b_idx].row;
			c[c_idx].column = b[b_idx].column;
			c[c_idx].value = b[b_idx].value;
			b_idx++;
			c[0].value =c_idx++;
		}

	}


	else // flag == 1 , 남아있는 a 처리
	{
		while (a_idx <= a[0].value)
		{
			c[c_idx].row = a[a_idx].row;
			c[c_idx].column = a[a_idx].column;
			c[c_idx].value = a[a_idx].value;
			a_idx++;
			c[0].value = c_idx++;
		}
	}


}



