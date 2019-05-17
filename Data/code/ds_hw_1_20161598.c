#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
int compare(int a, int b)
{
	if (a < b)
		return -1;
	else if (a == b)
		return 0;
	else
		return 1;
}
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
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
void readMatrix(FILE *fp, Term a[])
{
	int i = 1, n, cnt = 0;
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	while(fscanf(fp,"%d ",&n) != EOF)
	{
		if (n != 0)
		{
			a[i].row = cnt / a[0].column;
			a[i].column = (cnt % a[0].column);
			a[i].value = n;
			i++;
		}
		cnt++;
	 }
	a[0].value = i - 1;
}
void printMatrix(Term a[])
{
	int i = 0;
	for (i = 0; i <= a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int i = 1, j = 1, cnt = 1, totalc=0;
	while ( (i<=a[0].value) && (j<=b[0].value))
	{
		switch (compare(a[i].row, b[j].row)){
		case -1: 
		{
			while (1)
			{
				if (a[i].row >= b[j].row)
					break;
				c[cnt].row = a[i].row;
				c[cnt].column = a[i].column;
				c[cnt++].value = a[i].value;
				i++;
			}
			break;
		}
		case 0:
		{
			switch (compare(a[i].column, b[j].column))
			{
			case -1: {
				c[cnt].row = a[i].row;
				c[cnt].column = a[i].column;
				c[cnt++].value = a[i].value;
				i++;
				break;
			}
			case 0:
			{
				c[cnt].row = a[i].row;
				c[cnt].column = a[i].column;
				c[cnt++].value = a[i].value + b[j].value;
				i++;
				j++;
				break;
			}
			case 1:
			{
				c[cnt].row = b[j].row;
				c[cnt].column = b[j].column;
				c[cnt++].value = b[j].value;
				j++;
				break;
			}
			}
			break;
		}
		case 1:
		{
			while (1)
			{
				if (b[j].row >= a[i].row)
					break;
				c[cnt].row = b[j].row;
				c[cnt].column = b[j].column;
				c[cnt++].value = b[j].value;
				j++;
			}
			break;
		}
		}
	}
	for (; i <= a[0].value; i++)
	{
		c[cnt].row = a[i].row;
		c[cnt].column = a[i].column;
		c[cnt++].value = a[i].value;
	}
	for (; j <= b[0].value; j++)
	{
		c[cnt].row = b[j].row;
		c[cnt].column = b[j].column;
		c[cnt++].value = b[j].value;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = cnt-1;
}

