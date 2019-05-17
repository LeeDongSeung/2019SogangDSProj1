#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MAX_TERMS 1024

typedef struct
{
	int row, column, value;
} Term;

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
	int k = 1, count = 0;
	fscanf(fp, "%d %d", &(a[0].row), &(a[0].column));

	for (int i = 0; i < a[0].row; i++)
	{
		for (int j = 0; j < a[0].column; j++)
		{
			a[k].row = i;
			a[k].column = j;
			fscanf(fp, "%d", &(a[k].value));

			if (a[k].value != 0) // some modifications are there
			{
				count++;
				k++;
			}
		}
	}
	a[0].value = count;
	return;
}

void printMatrix(Term a[])
{
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value);
	for (int i = 1; i <= a[0].value; i++)
	{
		if (a[i].value == 0)
			continue;
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int i, j, num_rows = a[0].row, num_cols = a[0].column, num_terms = a[0].value, temp = 0, store = 0;
	int idx_a = 1, idx_b = 1;

	int k = 1;
	c[0].row = num_rows;
	c[0].column = num_cols;

	for (i = 0; i < num_rows; i++) // run a loop for all possible rows
	{
		for (j = 0; j < num_cols; j++) // loop for all possible columns
		{
			if (a[idx_a].row == i && a[idx_a].column == j) // when a matrix has value at (i,j) index
			{
				if (b[idx_b].row == i && b[idx_b].column == j) // when a and b both has the value at (i,j) index
				{
					c[k].row = a[idx_a].row;
					c[k].column = a[idx_a].column;
					c[k].value = a[idx_a].value + b[idx_b].value;
					if (c[k].value == 0)
						continue;
					idx_a++;
					idx_b++;
					k++;
				}
				else // when only a has value at (i,j) index
				{
					c[k].row = a[idx_a].row;
					c[k].column = a[idx_a].column;
					c[k].value = a[idx_a].value;
					idx_a++;
					k++;
				}
			}
			else if (b[idx_b].row == i && b[idx_b].column == j) // when only value at b at index (i,j)
			{
				c[k].row = b[idx_b].row;
				c[k].column = b[idx_b].column;
				c[k].value = b[idx_b].value;
				idx_b++;
				k++;
			}
		}
	}
	c[0].value = k - 1;
}
