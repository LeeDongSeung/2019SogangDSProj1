#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1024
#define COMPARE(x,y) x == y ? 0 : (x < y ? 1 : 2)

typedef struct
{
	int row;
	int col;
	int val;
} term;

void readMatrix(FILE* fp, term a[]);
void printMatrix(term a[]);
void matrixAdd(term a[], term b[], term c[]);



void readMatrix(FILE* fp, term inp[])
{
	int tempR, tempC, tempV;
	int i, j, pos;

	tempV = 0;
	pos = 0;

	if (fscanf(fp, "%d %d\n", &tempR, &tempC) != 2)
	{
		printf("\nIncorrect file format.\n");
		exit(1);
	}
	inp[0].row = tempR;
	inp[0].col = tempC;
	

	for (i = 0; i < inp[0].row; i++)
		for (j = 0; j < inp[0].col; j++)
		{
			if ((fscanf(fp, "%d", &tempV)) != 1)
			{
				printf("\nIncorrect file format.\n");
				exit(1);
			}

			if (tempV != 0)
			{
				pos++;
				inp[pos].row = i;
				inp[pos].col = j;
				inp[pos].val = tempV;
			}
		}

	inp[0].val = pos;
}

void printMatrix(term a[])
{
	int i;
	for (i = 0; i <= a[0].val; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].val);
}
void matrixAdd(term a[], term b[], term c[])
{
	int curA = 1;
	int curB = 1;
	int curC = 1;

	int Det;

	int finA = a[0].val;
	int finB = b[0].val;


	if (a[0].row != b[0].row || a[0].col != b[0].col)
	{
		printf("\nNot addable\n");
		exit(1);
	}

	c[0].row = a[0].row;
	c[0].col = a[0].col;

	while (curA <= finA && curB <= finB)
	{
		Det = (COMPARE(a[curA].row, b[curB].row));
		if (Det == 0)
			Det = (COMPARE(a[curA].col, b[curB].col));

		switch (Det)
		{
		case 0:	if (a[curA].val + b[curB].val != 0)
		{
			c[curC].row = a[curA].row;
			c[curC].col = a[curA].col;
			c[curC].val = a[curA].val + b[curB].val;
		}
				curA++; curB++; curC++; break;

		case 1:	c[curC].row = a[curA].row;
			c[curC].col = a[curA].col;
			c[curC].val = a[curA].val;
			curA++; curC++;	break;

		case 2:	c[curC].row = b[curB].row;
			c[curC].col = b[curB].col;
			c[curC].val = b[curB].val;
			curB++; curC++;	break;
		default:;
		}
	}

	while (curA <= finA)
	{
		c[curC].row = a[curA].row;
		c[curC].col = a[curA].col;
		c[curC].val = a[curA].val;
		curA++; curC++;
	}
	while (curB <= finB)
	{
		c[curC].row = b[curB].row;
		c[curC].col = b[curB].col;
		c[curC].val = b[curB].val;
		curB++; curC++;
	}

	c[0].val = curC - 1;
}

int main()
{
	term a[MAX_TERMS];
	term b[MAX_TERMS];
	term c[MAX_TERMS];
	FILE* fp;

	fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);

	return 0;
}