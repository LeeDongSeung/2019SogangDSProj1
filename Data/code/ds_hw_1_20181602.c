#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, col, val;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE *fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp = fopen("a.txt","r");
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("b.txt","r");
	readMatrix(fp,b);
	fclose(fp);
	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE *fp, Term a[])
{
	int row, col, i, j=0, k=0, cnt =1, tmp;
	fscanf(fp, "%d %d", &row, &col);
	a[0].row = row;
	a[0].col = col;

	for(i=0; i < row * col; i++)
	{
		fscanf(fp, "%d ", &tmp);
		if(tmp){
			a[cnt].row = j; a[cnt].col = k;
			a[cnt].val = tmp;
			cnt++;
		}
		k++;
		if(k==col){
			j++;
			k = 0;
		}
	}
	a[0].val = cnt-1;

}

void printMatrix(Term a[])
{
	printf("%d %d \n", a[0].row, a[0].col);
	for(int i=1;i<=a[0].val;i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].val);
	}
	return;
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int cnt=0;
	for(int i=1;i<=a[0].val;i++)
	{
			if(a[i].val != 0 || b[0].val != 0)
			{
				cnt++;
				c[cnt].col = a[i].col;
				c[cnt].row = a[i].row;
				c[cnt].val = a[i].val+b[i].val;
			}
	}
	c[0].col = a[0].col;
	c[0].row = a[0].row;
	c[0].val = cnt;

}
