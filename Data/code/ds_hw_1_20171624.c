#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	int row, column, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE*fp = fopen("A.txt", "r");
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
	int i,temp,num_row,num_col;

	fscanf(fp, "%d %d\n", &num_row, &num_col);

	int p = num_row*num_col;
	a[0].row = num_row; a[0].column = num_col; a[0].value = p;

	for (i = 1; i <= p; i++)
	{
		if (i%num_col == 0)
		{
			fscanf(fp, "%d", &temp);
			a[i].row = i / num_col-1;
			a[i].column = num_col-1;
			a[i].value = temp;
		}//row의 마지막 배열원소를 받을 때는 column의 계산이 다름으로 구분하였다.
		else
		{
			fscanf(fp, "%d", &temp);
			a[i].row = i / num_col;
			a[i].column = i % num_col - 1;
			a[i].value = temp;
		}
		
	}//배열의 개수를 n이라고 할때 시간복잡도는  O(n)이다.

}
void printMatrix(Term a[]) 
{
	int i,temp=a[0].value;
	int s = a[0].value;
	for (i = 1; i <= a[0].value; i++)
		if (a[i].value == 0)temp--;//value=0인 배열의 개수를 제외한다.
	
	a[0].value = temp;//먼저 출력되는 a[0].value의 값을 먼저 바꾸어준다.
	
	for (i = 0; i <= s; i++)
	{
		if (a[i].value != 0)
			printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}//value=0인 배열을 출력하지 않음으로 희소행렬형태로 출력한다.
	//배열의 개수를 n이라고 할때 시간복잡도는  O(n)이다.
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	c[0].column = a[0].column;
	c[0].row = a[0].row;
	int p=c[0].value = a[0].value;

	int i;

	for (i = 1; i <= p; i++)
	{
		c[i].row = a[i].row;
		c[i].column = a[i].column;
		c[i].value = a[i].value + b[i].value;
	}//row와 col의 값을  Term a에서 가져와 계산을 최소화하였다.
	//배열의 개수를 n이라고 할때 시간복잡도는  O(n)이다.
	
}
