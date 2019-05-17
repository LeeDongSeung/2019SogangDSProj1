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

	system("PAUSE");
	return 0;
}
void readMatrix(FILE* fp, Term a[])
{
	int n, m;
	fscanf(fp, "%d%d", &n, &m);      
	
	int p = 1;
	a[0].row = n; a[0].column = m;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) {
			int t;
			fscanf(fp, "%d", &t);    
			
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	a[0].value = (p - 1);
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int skip = 0;
	int n, m, x;
	int p = 1;
	n = a[0].row;
	m = a[0].column;
	x = a[0].value;

	c[0].row = n; c[0].column = m;
	for (int i = 1; i <= x; i++)
			if ((a[i].value != 0) || (b[i].value != 0)) {
				c[p].row     = a[i].row;
				c[p].column  = a[i].column;
				c[p++].value = a[i].value + b[i].value;
		    }
			else skip++;
	c[0].value = (p - 1);
}
void printMatrix(Term a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
