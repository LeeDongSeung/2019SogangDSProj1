#include	<stdio.h>
#include	<stdlib.h>

#define MAX_TERMS 1024

typedef struct{
	int row, column, value;
} Term;

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term [], Term [], Term []);

int main(){
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);
	
	return 0;
}

void readMatrix(FILE* fp, Term a[]){
	int i, j;
	int count = 0;
	fscanf(fp, "%d%d", &a[0].row, &a[0].column);
	for(i=0 ; i<a[0].row ; i++){
		for(j=0 ; j<a[0].column ; j++){
			fscanf(fp, "%d", &a[++count].value);
			a[count].row = i;
			a[count].column = j;
			if(a[count].value == 0)
				count--;
		}
	}
	a[0].value = count;
}

void printMatrix(Term a[]){
	int i;
	for(i=0 ; i<=a[0].value ; i++){
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]){
	int i, j;
	int count = 0;

	for(i=1, j=1 ; i<=a[0].value && j<=b[0].value ; ){
		if(a[i].row == b[j].row && a[i].column == b[j].column){
			c[++count].row = a[i].row;
			c[count].column = a[i].column;
			c[count].value = a[i].value + b[j].value;
			i++;	
            j++;
		}
		else if(a[i].row > b[j].row || a[i].column > b[j].column){
			c[++count].row = b[j].row;
			c[count].column = b[j].column;
			c[count].value = b[j].value;
			j++;
		}
		else if(b[j].row > a[i].row || b[j].column > a[i].column){
			c[++count].row = a[i].row;
			c[count].column = a[i].column;
			c[count].value = a[i].value;
			i++;
		}
	}
	for( ; i<=a[0].value ; i++){
		c[++count].row = a[i].row;
		c[count].column = a[i].column;
		c[count].value = a[i].value;
	}
	for( ; i<=b[0].value ; j++){
		c[++count].row = b[j].row;
		c[count].column = b[j].column;
		c[count].value = b[j].value;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = count;
}
