#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 1024

int num_row;
int num_col;
int num_a;
int num_b;

void readMatrix(FILE* fp,Term a[]) // 파일을 읽어서 희소행렬로 만든다.
{
	int input = 0;
	int i,j;
	int count = 1;

	if(fp == NULL)
	{
		printf("file read error!!\n");
		exit(1);
	}

	fscanf(fp,"%d",&num_row);
	fscanf(fp,"%d",&num_col);

	a[0].column = num_col;
	a[0].row = num_row;

	for(i=0;i<num_row;i++)
	{
		for(j=0;j<num_col;j++)
		{
			fscanf(fp,"%d",&input);
			a[count].row=i;
			a[count].column=j;
			a[count].value=input;

			count++;
		}
	}

}

void printMatrix(Term a[])
{
	int i = 0;
	int j = 0;

	for(i=0;i<num_col*num_row+1;i++)
	{
		if(a[i].value != 0)
			printf("%d %d %d\n",a[i].row,a[i].column,a[i].value);
	}
}

void matrixAdd(Term a[],Term b[],Term c[])
{
	int i, j;
	int count = 0;

	c[0].column = num_col;
	c[0].row = num_row;

	for(i=1;i<num_col*num_row+1;i++)
	{
		c[i].row = a[i].row;
		c[i].column = a[i].column;
		c[i].value = a[i].value + b[i].value;
		if(c[i].value != 0)
			count++;
	}

	c[0].value = count;
}

int main() {

	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt","r");

	readMatrix(fp,a);

	fclose(fp);

	fp = fopen("B.txt","r");

	readMatrix(fp,b);

	fclose(fp);

	matrixAdd(a,b,c); // a와 b를 더해서 c로 만든다.

	printMatrix(c);

	return 0;
}