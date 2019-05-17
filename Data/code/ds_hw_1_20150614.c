#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
typedef struct {
	int row, column, value;
}Term;
#define MAX_TERMS 1024
#define COMPARE(x,y) (((x) > (y)) ? 1: ((x) < (y)) ? -1:0)
void readMatrix(FILE*fp, Term a[])
{
	int i = -1, j = 0, k = 1;
	int arr[32][32] = { 0, };
	while (1)
	{
		if (i == -1)
		{
			fscanf(fp, "%d %d", &a[0].row, &a[0].column);
			i++;
		}
		char t = fscanf(fp, "%d", &arr[i][j]);
		if (t == EOF) break;
		if (arr[i][j] != 0)
		{
			a[k].row = i;
			a[k].column = j;
			a[k].value = arr[i][j];
			k++;
		}
		j++;
		if (j == a[0].column) 
		{ 
			i++;
			j = 0;
		}
	}
	a[0].value = --k;
	return;
}
void printMatrix(Term a[])
{
	for (int i = 0; i <= a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
	return;
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int i = 1, j = 1, k = 1;
	int totala = a[0].value, totalb = b[0].value;
	while (i <= totala && j <= totalb)
	{
		switch (COMPARE(a[i].row, b[j].row))
		{
			case 1:
			{
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k++].value = b[j++].value;
				break;
			}
			case 0:
			{
				switch (COMPARE(a[i].column, b[j].column))
				{
					case 1:
					{
						c[k].row = b[j].row;
						c[k].column = b[j].column;
						c[k++].value = b[j++].value;
						break;
					}
					case 0:
					{
						c[k].row = b[j].row;
						c[k].column = b[j].column;
						c[k++].value = b[j++].value + a[i++].value;
						break;
					}
					case -1:
					{
						c[k].row = a[i].row;
						c[k].column = a[i].column;
						c[k++].value = a[i++].value;
					}
				}
				break;
			}
			case -1:
			{
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k++].value = a[i++].value;
			}
		}
	}
	while (i <= totala)
	{
		c[k].row = a[i].row;
		c[k].column = a[i].column;
		c[k++].value = a[i++].value;
	}
	while(j <= totalb)
	{
		c[k].row = b[j].row;
		c[k].column = b[j].column;
		c[k++].value = b[j++].value;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = --k;
	return;
}
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