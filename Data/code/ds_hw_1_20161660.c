#include<stdio.h>
#include<stdlib.h>
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
	
	FILE* fp = fopen("A.txt", "r");
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
	int i, j, k = 1, num;
	int a_value = 0;
	fscanf(fp, "%d%d", &(a[0].row), &(a[0].column));
	for (i = 0; i < a[0].row; i++)
	{
		for (j = 0; j < a[0].column; j++)
		{
			fscanf(fp, "%d", &num);
			if (num != 0)
			{
				a[k].row = i;
				a[k].column = j;
				a[k].value = num;
				k++;
				a_value++;
			}
		}
	}
	a[0].value = a_value;
}
void printMatrix(Term a[])
{
	int i;
	for (i = 0; i <= a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int i = 1, j = 1;
	int k = 1;
	int sum;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	while (i <= a[0].value && j <= b[0].value)
	{
		if (a[i].row > b[j].row)
		{
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			k++;
			j++;
		}
		else if (a[i].row == b[j].row)
		{
			if (a[i].column > b[j].column)
			{
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = b[j].value;
				k++;
				j++;
			}
			else if (a[i].column == b[j].column)
			{
				sum = a[i].value + b[j].value;
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = sum;
				k++;
				i++;
				j++;
			}
			else
			{
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				k++;
				i++;
			}
		}
		else
		{
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			k++;
			i++;
		}
	}
	for (; i <= a[0].value; i++)
	{
		c[k].row = a[i].row;
		c[k].column = a[i].column;
		c[k].value = a[i].value;
		k++;
	}
	for (; j <= b[0].value; j++)
	{
		c[k].row = b[j].row;
		c[k].column = b[j].column;
		c[k].value = b[j].value;
		k++;
	}
	c[0].value = k - 1;
}