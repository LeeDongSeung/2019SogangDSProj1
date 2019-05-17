#include <stdio.h>
#include <stdlib.h>
typedef struct {
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
	int n, m;
	fscanf(fp,"%d%d", &n, &m);
	int p = 1;
	a[0].row = n; a[0].column = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int t;
			fscanf(fp, "%d", &t);
			if (t == 0) continue;
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	a[0].value = p - 1;
}

void printMatrix(Term a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	if (a[0].row != b[0].row || a[0].column != b[0].column)
	{
		printf("Incompatible matrices");
		return;
	}
	int totala = a[0].value, totalb = b[0].value;
	int totalc = 0;
	c[0].row = a[0].row, c[0].column = a[0].column;
	int i = 1, j = 1;
	for (; i <= totala && j <= totalb;)
	{
		int add_a = a[i].row * a[0].column + a[i].column;
		int add_b = b[j].row * b[0].column + b[j].column;
		if (add_a < add_b)
		{
			c[++totalc].row = a[i].row;
			c[totalc].column = a[i].column;
			c[totalc].value = a[i].value;
			i++;
		}
		else if (add_a > add_b)
		{
			c[++totalc].row = b[j].row;
			c[totalc].column = b[j].column;
			c[totalc].value = b[j].value;
			j++;
		}
		else
		{
			c[++totalc].row = a[i].row;
			c[totalc].column = a[i].column;
			c[totalc].value = a[i].value + b[j].value;
			i++, j++;
		}
	}
	for (i; i <= totala; i++)
	{
		c[++totalc].row = a[i].row;
		c[totalc].column = a[i].column;
		c[totalc].value = a[i].value;
	}
	for (j; j <= totalb; j++)
	{
		c[++totalc].row = b[j].row;
		c[totalc].column = b[j].column;
		c[totalc].value = b[j].value;
	}
	c[0].value = totalc;
}