#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
void attach(Term a[], Term b[], int*, int*);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp=fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);
	fp=fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;	
}

void readMatrix(FILE *fp, Term a[])
{
	int i, j;
	int rowNumbers, colNumbers, temp, cnt=1;
	fscanf(fp, "%d %d", &rowNumbers, &colNumbers);
	a[0].row=rowNumbers;
	a[0].column=colNumbers;
	for(i=0; i<rowNumbers; i++) {
		for(j=0; j<colNumbers; j++) {
			fscanf(fp, "%d", &temp);
			if(!temp) continue;
			else {
				a[cnt].row=i;
				a[cnt].column=j;
				a[cnt++].value=temp;
			}
		}	
	}
	a[0].value=cnt-1;
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int i=1, j=1;
	int a_terms=a[0].value;
	int b_terms=b[0].value;
	int cnt=1;
	int element;
	c[0].row=a[0].row;
	c[0].column=a[0].column;
	
	while(i<=a_terms && j<=b_terms) {
		if(a[i].row==b[j].row) {
			if(a[i].column>b[j].column) {
				attach(b, c, &cnt, &j);
				
//				c[cnt].row=b[j].row;
//				c[cnt].column=b[j].column;
//				c[cnt++].value=b[j++].value;
			}
			else if(a[i].column<b[j].column) {
				attach(a, c, &cnt, &i);
//				c[cnt].row=a[i].row;
//				c[cnt].column=a[i].column;
//				c[cnt++].value=a[i++].value;
			}
			else {
				element=a[i].value+b[j].value;
				if(element) {
					c[cnt].row=a[i].row;
					c[cnt].column=a[i].column;
					c[cnt++].value=element;
					i++;
					j++;
				}
				else {
					i++;
					j++;	
				}
			}
		}
		else if(a[i].row>b[j].row) {
			for( ; a[i].row>b[j].row; ) {
				attach(b, c, &cnt, &j);
				
//				c[cnt].row=b[j].row;
//				c[cnt].column=b[j].column;
//				c[cnt++].value=b[j++].value;
			}
		}
		else {
			for( ; a[i].row<b[j].row; ) {
				attach(a, c, &cnt, &i);	
							
//				c[cnt].row=a[i].row;
//				c[cnt].column=a[i].column;
//				c[cnt++].value=a[i++].value;
			}				
		}
			
	}
	for( ; i<=a_terms; ) {
		attach(a, c, &cnt, &i);	
			
//		c[cnt].row=a[i].row;
//		c[cnt].column=a[i].column;
//		c[cnt++].value=a[i++].value;
	}
	for( ; j<=b_terms; ) {
		attach(b, c, &cnt, &j);
//		c[cnt].row=b[j].row;
//		c[cnt].column=b[j].column;
//		c[cnt++].value=b[j++].value;
	}
	c[0].value=cnt-1;				
}
void attach(Term a[], Term b[], int* cnt, int* index)
{
	b[*cnt].row=a[*index].row;
	b[*cnt].column=a[*index].column;
	b[(*cnt)++].value=a[(*index)++].value;
}


void printMatrix(Term a[])
{
	int i;
	for(i=0; i<=a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}
