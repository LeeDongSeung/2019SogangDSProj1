#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int row, column, value;
}Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void){

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


void printMatrix(Term a[]){
	int i;

	for(i = 0; i <= a[0].value; i++){
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]){

	int i;
	int startA, startB;
	int aL, bL;
	int sum;
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	i = 1;
	startA = 1; startB = 1;
	while((startA <= a[0].value) && (startB <= b[0].value)){
		aL = 0 + a[startA].column + (a[0].column * a[startA].row);
		bL = 0 + b[startB].column + (b[0].column * b[startB].row);
		if(aL < bL){
			c[i].row = a[startA].row;	
			c[i].column = a[startA].column;	
			c[i++].value = a[startA++].value;	
		}
		else if(aL == bL){
			sum = a[startA].value + b[startB].value;
			if(sum){
				c[i].row = a[startA].row;	
				c[i].column = a[startA].column;	
				c[i++].value = sum;	
			}
			startA++; startB++;
		}
		else{
			c[i].row = b[startB].row;	
			c[i].column = b[startB].column;	
			c[i++].value = b[startB++].value;	
		}
	}

	for(; startA<= a[0].value; startA++){
		c[i].row = a[startA].row;	
		c[i].column = a[startA].column;	
		c[i++].value = a[startA].value;
	}
	for(; startB<= b[0].value; startB++){
		c[i].row = b[startB].row;	
		c[i].column = b[startB].column;	
		c[i++].value = b[startB].value;
	}	
	c[0].value = i-1;

	return;
}

void readMatrix(FILE* fp, Term a[]){

	int tempRow, tempCol, tempValue;
	int i;

	i = 0;
	if(fscanf(fp, "%d %d", &tempRow, &tempCol)){
		if(tempCol * tempRow >= MAX_TERMS){
			fprintf(stderr, "Error\n");
			exit(1);
		}
		a[i].row = tempRow;
		a[i++].column = tempCol;

		tempRow = 0; tempCol = 0;
		while(fscanf(fp, "%d", &tempValue) != EOF){
			if(tempValue){
				a[i].row = (int)((tempRow)/(a[0].column));
				a[i].column = (tempCol)%(a[0].column);
				a[i++].value = tempValue;
			}
			tempRow++; tempCol++;
		}

	}
	a[0].value = i-1;

	return;
}

