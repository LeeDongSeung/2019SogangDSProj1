#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, col, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE *fp, Term a[])
{
	int i, j, t=1, k;
	fscanf(fp, "%d %d", &a[0].row, &a[0].col);
	for(i=0;i<a[0].row;i++){
		for(j=0;j<a[0].col;j++){
			if(fscanf(fp, "%d", &k)!=EOF){
				if(k!=0){
					a[t].row=i;
					a[t].col=j;
					a[t].value=k;
					t++;
				}
			}
		}
	}a[0].value=t-1;
}
void printMatrix(Term a[])
{
	int i;
	for(i=0;i<=a[0].value;i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	}
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	int i=1, j=1, k=1;
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	c[0].value = 0;

	while(i<=a[0].value && j<=b[0].value){
			if(a[i].row < b[j].row){
				c[k].row=a[i].row;
				c[k].col=a[i].col;
				c[k].value=a[i].value;
				k++;i++;
			}
			else if(a[i].row == b[j].row){
				if(a[i].col < b[j].col){
					c[k].row=a[i].row;
					c[k].col=a[i].col;
					c[k].value=a[i].value;
					k++;i++;
				}
				else if(a[i].col == b[j].col){
					c[k].row=a[i].row;
					c[k].col=a[i].col;
					c[k].value=a[i].value + b[j].value;
					k++;i++;j++;
				}
				else if(a[i].col > b[j].col){
					c[k].row=b[j].row;
					c[k].col=b[j].col;
					c[k].value=b[j].value;
					k++;j++;
				}
			}
			else {
				c[k].row=b[j].row;
				c[k].col=b[j].col;
				c[k].value=b[j].value;
				k++;j++;
			}
	}
	for(;i<=a[0].value;i++){
		c[k].row=a[i].row;
		c[k].col=a[i].col;
		c[k].value=a[i].value;
		k++;
	}
	for(;j<=b[0].value;j++){
		c[k].row=b[j].row;
		c[k].col=b[j].col;
		c[k].value=b[j].value;
		k++;
	}
	c[0].value=k-1;
	
}
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);
//printMatrix(a);
	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);
//printMatrix(b);
	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}
 
