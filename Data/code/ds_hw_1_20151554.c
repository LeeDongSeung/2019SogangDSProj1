#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row;
	int column;
	int value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term C[]);
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	fscanf(fp, "%d %d", &a[0].row,&a[0].column);
	a[0].value = 0;
	int tmp;
	int i = 1;
	while (fscanf(fp, "%d", &tmp) != EOF)
	{
		if (tmp != 0)
			a[0].value++;
	}
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	for (int j = 0; j < a[0].row; j++)
	{
		for (int k = 0; k < a[0].column; k++)
		{
			fscanf(fp, "%d", &tmp);
			if (tmp != 0)
			{
				a[i].value = tmp;
				a[i].row = j;
				a[i].column = k;
				i++;
			}
		}
	}

}
void printMatrix(Term a[]) {
	for (int i = 0; i <=a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;

	int i = 1;
	int j = 1;
	int k = 1;
	int sum;

	while (i<=a[0].value&&j<=b[0].value)
	{
		if (a[i].row < b[j].row)
		{
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++;
			k++;
			c[0].value++;
		}
		else if (a[i].row == b[j].row)
		{
			if (a[i].column < b[j].column)
			{
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				i++;
				k++;
				c[0].value++;
			}
			else if (a[i].column == b[j].column)
			{
				sum = a[i].value + b[j].value;
				if (sum)
				{
					c[k].row = a[i].row;
					c[k].column = a[i].column;
					c[k].value = sum;
					c[0].value++;
				}
				i++;
				j++;
				k++;
			}
			else if (a[i].column > b[j].column)
			{
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = b[j].value;
				j++;
				k++;
				c[0].value++;
			}
		}
		else if (a[i].row > b[j].row)
		{
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++;
			k++;
			c[0].value++;
		}
	}
	
	for (i; i<=a[0].value; i++)
	{
		c[k].row = a[i].row;
		c[k].column = a[i].column;
		c[k].value = a[i].value;
		k++;
		c[0].value++;
	}
	for (j; j<=b[0].value; j++)
	{
		c[k].row = b[j].row;
		c[k].column = b[j].column;
		c[k].value = b[j].value;
		k++;
		c[0].value++;
	}
}