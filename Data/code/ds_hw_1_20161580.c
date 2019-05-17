#define MAX_TERMS 1024
typedef struct {
	int col;
	int row;
	int value;
}Term;

#include <stdio.h>
#include <stdlib.h>

void readMatrix(FILE* fp, Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
void printMatrix(Term a[]);
int main(void)
{

	Term *a = (Term*)malloc(sizeof(Term)*MAX_TERMS);
	Term *b = (Term*)malloc(sizeof(Term)*MAX_TERMS);
	Term *c = (Term*)malloc(sizeof(Term)*MAX_TERMS);

	FILE *fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	
	matrixAdd(a,b,c);
	printMatrix(c);
	return 0;
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	
	int i, j, k; j = 1; k = j;
	int count = 0;
	for (i = 1; i <= a[0].value; ) {
		
		if (j == b[0].value + 1)
		{
			while (i <= a[0].value) {
				c[k].value = a[i].value; c[k].row = a[i].row; c[k].col = a[i].col;	k++;
				i++;
			}
			break;
		}

		if (a[i].row == b[j].row) {
			if (a[i].col < b[j].col) {
				c[k].value = a[i].value; c[k].row = a[i].row; c[k].col = a[i].col;	k++;
				i++;
			}
			else if (a[i].col == b[j].col) {
				c[k].value = a[i].value + b[j].value; c[k].row = a[i].row; c[k].col = a[i].col;	k++;
				i++;	j++; count++;
			}
			else {
				c[k].value = b[j].value; c[k].row = b[j].row; c[k].col = b[j].col;	k++;
				j++;
			}
		}
		
		else if (a[i].row > b[j].row) {
			while (a[i].row != b[j].row) {
				c[k].value = b[j].value; c[k].row = b[j].row; c[k].col = b[j].col;	k++;
				j++;
			}
		}
		
		else {
			if (a[i].value == 0 || b[j].value == 0) break;
			while (a[i].row != b[j].row) {
				c[k].value = a[i].value; c[k].row = a[i].row; c[k].col = a[i].col;	k++;
				i++;
			}
		}
	}
	while (j <= b[0].value)
	{
		c[k].value = b[j].value; c[k].row = b[j].row; c[k].col = b[j].col;	k++;
		j++;
	}
	
	c[0].row = a[0].row; c[0].col = a[0].col; c[0].value = --k;
}

void readMatrix(FILE* fp, Term a[])
{
	
	int row, col;
	int i, j, temp;
	int turn = 1;
	
	fscanf(fp, "%d %d", &row, &col);
	a[0].row = row;	a[0].col = col;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				a[turn].row = i;
				a[turn].col = j;
				a[turn++].value = temp;
			}
		}
	}
	a[0].value = --turn;
}

void printMatrix(Term c[])
{
	int i = 0;
	while (i <= c[0].value) {
		printf("%d	%d	%d\n", c[i].row, c[i].col, c[i].value);
		i++;
	}
}

