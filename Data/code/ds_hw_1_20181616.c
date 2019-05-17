#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row, column, value;
} Term;

#define MAX_TERMS 1024
void readMatrix(FILE* fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[]);

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

void readMatrix(FILE* fp, Term a[])
{
	fscanf(fp, "%d", &a[0].row);
	fscanf(fp, "%d", &a[0].column);
	int temp, count = 1;

	for(int i = 0; i < a[0].row; i++)
	{
		for (int j = 0; j < a[0].column; j++)
		{
			fscanf(fp, "%d", &temp);
			if (temp != 0)
			{
				a[count].row = i;
				a[count].column = j;
				a[count].value = temp;
				count++;
			}
		}
	}

	a[0].value = --count;

	return;
}

void printMatrix(Term a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);

}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int count = 1, i = 1, j = 1;
	for (; ; count++)
	{
		if (a[i].row == b[j].row)
		{
			if (a[i].column > b[j].column)
			{
				c[count].row = b[j].row;
				c[count].column = b[j].column;
				c[count].value = b[j].value;
				j++;
			}
			else if (a[i].column < b[j].column)
			{
				c[count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value;
				i++;
			}
			else
			{
				c[count].row = a[i].row;
				c[count].column = a[i].column;
				c[count].value = a[i].value + b[j].value;
				i++; j++;
			}
		}
		else if (a[i].row > b[j].row)
		{
			c[count].row = b[j].row;
			c[count].column = b[j].column;
			c[count].value = b[j].value;
			j++;
		}
		else
		{
			c[count].row = a[i].row;
			c[count].column = a[i].column;
			c[count].value = a[i].value;
			i++;
		}

		if (i > a[0].value || j > b[0].value)
			break;

	}

	count++;
	if (i <= a[0].value)
	{
		for (; i <= a[0].value; i++)
		{
			c[count].row = a[i].row;
			c[count].column = a[i].column;
			c[count].value = a[i].value;
			count++;
		}
	}
	else if (j <= b[0].value)
	{
		for (; j <= b[0].value; j++)
		{
			c[count].row = b[j].row;
			c[count].column = b[j].column;
			c[count].value = b[j].value;
			count++;
		}
	}
	
	c[0].value = --count;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
}