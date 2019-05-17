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
void readMatrix(FILE* fp, Term a[]) {
	int count = 1;
	fscanf(fp, "%d", &a[0].row);
	fscanf(fp, "%d", &a[0].column);
	if (a[0].row > 20 || a[0].column>20)
	{
		printf("error.row or colum con't > 20");
		return;
	}

	for (int i = 0; i < a[0].row;i++)
	{
		for (int j = 0; j < a[0].column;j++)
		{
			fscanf(fp, "%d", &a[count].value);
			a[count].row = i;
			a[count].column = j;
			count++;
		}
	}
	
	a[0].value = count - 1;
	return;
	
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int count =0;

	c[0].row = a[0].row;
	c[0].column = a[0].column;
	for (int i = 0; i < c[0].row;i++)
	{
		for (int j = 0; j < c[0].column;j++)
		{
				
				count++;
				c[count].value = a[count].value + b[count].value;				
				c[count].row = i;
				c[count].column = j;
				
						
		}
	}
	c[0].value = count ;
	return;
}
void printMatrix(Term a[]) {
	int count=0;
	for (int k = 0; k <= a[0].value;k++)
	{
		if (a[k].value==0)
		{
			count++;
		}
	}
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value-count);
	for (int k = 1; k <=a[0].value;k++)
	{		
		if (a[k].value==0)
		{
			continue;
		}
		printf("%d %d %d\n", a[k].row, a[k].column,a[k].value);		
	}	
	return;
}