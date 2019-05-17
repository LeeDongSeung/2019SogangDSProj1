#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
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
void readMatrix(FILE* fp, Term a[])
{
	int row, col, val;
	fscanf(fp, "%d %d", &row, &col);
	a[0].column = col;
	a[0].row = row;
	a[0].value = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fscanf(fp, "%d", &val);
			if (val != 0)
			{
				a[0].value++;
				a[a[0].value].column = j;
				a[a[0].value].row = i;
				a[a[0].value].value = val;
			}
		}
	}

}
void printMatrix(Term a[])
{
	for (int i = 0; i < a[0].value; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int inda = 1, indb = 1, indc = 1;
	if (a[0].row != b[0].row || a[0].column != b[0].column)
	{
		printf("ERROR");
		return;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;
	while (inda-1 <= a[0].value && indb-1 <= b[0].value)
	{
		int loca = a[inda].row*a[0].column + a[inda].column;
		int locb = b[indb].row*b[0].column + b[indb].column;
		if (loca < locb)
		{
			c[indc++] = a[inda++];
		}
		else if (loca == locb) {
			
				c[indc].row = a[inda].row;
				c[indc].column = a[inda].column;
				c[indc++].value = a[inda++].value + b[indb++].value;
	
		}
		else
			c[indc++] = b[indb++];

	}
	for (; inda <= a[0].value; )
	{
		c[indc++] = a[inda++];
	}
	for (; indb <= b[0].value; )
	{
		c[indc++] = b[indb++];
	}
	c[0].value = indc-2;
}
