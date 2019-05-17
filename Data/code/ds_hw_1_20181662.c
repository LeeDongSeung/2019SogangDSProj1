#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int row, column, value;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt", "r");	//A행렬의 값 읽어옴
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");	//B행렬의 값 읽어옴
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);	//두 행렬의 합을 c행렬에 저장
	printMatrix(c);	//c행렬 출력

	return 0;
}

void readMatrix(FILE* fp, Term a[])
{
	int rowNum, colNum;
	int temp = 0;
	fscanf(fp, "%d %d", &rowNum, &colNum);
	a[0].row = rowNum; a[0].column = colNum;
	
	int loopCount = 0;

	int i = 0 ; int j = 0; int count = 0;
	int num = 1;
	while(loopCount < a[0].row * a[0].column)
	{
		fscanf(fp, "%d", &temp);
		
		if(temp != 0)
		{
			a[num].value = temp;
			a[num].row = i;
			a[num].column = j;
			count++;
			num++;
		}
		j++;
		if(j >= a[0].column)
		{
			i++;
			j = 0;
		}
		loopCount++;
	}
	a[0].value = count;
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int indexA = 1;
	int indexB = 1;
	int indexC = 1;

	c[0].row = a[0].row; c[0].column = a[0].column;
	for(int i = 1; i < MAX_TERMS; i++)
	{
		c[i].row = 0;
		c[i].column = 0; 
		c[i].value = 0;
	}

	while(indexA <= a[0].value && indexB <= b[0].value)
	{
		if(a[indexA].row == b[indexB].row)
		{
			if(a[indexA].column == b[indexB].column)
			{
				c[indexC].row = a[indexA].row;
				c[indexC].column = a[indexA].column;
				c[indexC].value = a[indexA].value + b[indexB].value;
				indexA++;
				indexB++;
				indexC++;
			}
			else
			{
				if(a[indexA].column < b[indexB].column)
				{
					c[indexC].row = a[indexA].row;
					c[indexC].column = a[indexA].column;
					c[indexC].value = a[indexA].value;
					indexA++;
					indexC++;
				}
				else
				{
					c[indexC].row = b[indexB].row;
					c[indexC].column = b[indexB].column;
					c[indexC].value = b[indexB].value;
					indexB++;
					indexC++;
				}
			}
		}
		else
		{
			if(a[indexA].row < b[indexB].row)
			{
				c[indexC].row = a[indexA].row;
				c[indexC].column = a[indexA].column;
				c[indexC].value = a[indexA].value;
				indexA++;
				indexC++;
			}
			else
			{
				c[indexC].row = b[indexB].row;
				c[indexC].column = b[indexB].column;
				c[indexC].value = b[indexB].value;
				indexB++;
				indexC++;
			}
		}
	}
	if(indexA < a[0].value)
	{
		while(indexA <= a[0].value)
		{
			c[indexC].row = a[indexA].row;
			c[indexC].column = a[indexA].column;
			c[indexC].value = a[indexA].value;
			indexA++;
			indexC++;
		}
	}
	else if(indexB < b[0].value)
	{
		while(indexB <= b[0].value)
		{
			c[indexC].row = b[indexB].row;
			c[indexC].column = b[indexB].column;
			c[indexC].value = b[indexB].value;
			indexB++;
			indexC++;
		}
	}
	c[0].value = indexC - 1;


}

void printMatrix(Term a[])
{
	for(int i = 0; i <= a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
