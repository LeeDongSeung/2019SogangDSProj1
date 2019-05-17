#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void)
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	
	FILE *fp = fopen("A.txt", "r");
	readMatrix(fp,a);
	fclose(fp);
	
	fp = fopen("B.txt", "r");
	readMatrix(fp,b);
	fclose(fp);
	
	matrixAdd(a,b,c);
	printMatrix(c);
	
	return 0;
}

void readMatrix(FILE* fp, Term a[])
{
	int row, col, i, j=0, k=0, count =1, temp;
	fscanf(fp, "%d %d", &row, &col);
	a[0].row = row; a[0].column = col;
	
	for(i=0; i < row * col; i++){
		fscanf(fp, "%d ", &temp);
		if(temp){
			a[count].row = j; a[count].column = k;
			a[count].value = temp;
			count++;
		}
		k++;
		if(k==col){
			j++;
			k = 0;
		}
	}
	a[0].value = count-1;
}

void printMatrix(Term a[])
{
	int i, count;
	count = a[0].value;
	for(i=0; i<count+1; i++){
		printf("%d %d %d \n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	int i;
	int counta = 1, countb = 1, countc = 1;
	c[0].row = a[0].row; c[0].column = a[0].column;
	while(counta <= a[0].value && countb <= b[0].value){
		int ap = a[counta].row * a[0].column + a[counta].column;
		int bp = b[countb].row * b[0].column + b[countb].column;
		if(ap > bp){
			c[countc] = b[countb];
			countc++; countb++;
		}
		else if(ap == bp){
			c[countc].row = a[counta].row;
			c[countc].column = a[counta].column;
			c[countc].value = a[counta].value + b[countb].value;
			counta++; countb++; countc++;
		}
		else{
			c[countc] = a[counta];
			countc++; counta++;
		}
	}
	for(; counta <= a[0].value;){
		c[countc] = a[counta];
		countc++; counta++;
	}
	for(; countb <= b[0].value;){
		c[countc] = b[countb];
		countc++; countb++;
	}
	c[0].value = countc-1;
		
}
