#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int COMPARE(int x, int y);
void storeSum(Term d[], int *totalC, int row, int column, int sum);
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp;
	fp = fopen("A[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("B[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	matrixAdd(a, b, c);
	//printf("start printing matrix\n");
	printMatrix(c);
	return 0;
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j, totalc = 0, row_index, sum;
	int rows_a = a[0].row, cols_a = a[0].column, totala = a[0].value;
	int rows_b = b[0].row, cols_b = b[0].column, totalb = b[0].value;


	if ((rows_a != rows_b) || (cols_a != cols_b)) {
		fprintf(stderr, "incompatibloe matrixes\n");
		exit(1);
	}
	else {
		c[0].row = a[0].row;
		c[0].column = a[0].column;
	}
	//int ROW = a[1].row, COL = a[1].column;

	//걍 혹시나 해서?
	a[totala + 1].row = rows_a;b[totalb + 1].row = rows_b;	b[totalb + 1].column = cols_b;
	//전체를 한 번에 굴린다
	for (i = 1, j=1; i <= totala, j<=totalb;) {
		
		if (a[i].row < b[j].row){
			row_index = i;
			for (; a[i].row == a[row_index].row; i++)
				storeSum(c, &totalc, a[i].row, a[i].column, a[i].value); }//b[j].row>
		else if (a[i].row > b[j].row) {
			row_index = j;
				for (; b[j].row == b[row_index].row; j++)
					storeSum(c, &totalc, b[j].row, b[j].column, b[j].value);		
		}
		else {
			if (a[i].column < b[j].column) {
				storeSum(c, &totalc, a[i].row, a[i].column, a[i].value);
				i++;}
			else if (a[i].column > b[j].column) {
				storeSum(c, &totalc, b[j].row, b[j].column, b[j].value);
				j++;}
			else {
				sum = a[i].value + b[j].value;
				if (sum)
					storeSum(c, &totalc, a[i].row, a[i].column, sum);
				i++, j++;}
		}//nested else
		//}//if row
	}//for i, j
	for(; i<=totala; i++)
		storeSum(c, &totalc, a[i].row, a[i].column, a[i].value);
	for(; j<=totalb; j++)
		storeSum(c, &totalc, b[j].row, b[j].column, b[j].value);
	c[0].value = totalc;
}//matrix Add

void printMatrix(Term a[]) {
	int n = a[0].value;
	//printf("row col value|n");
	for (int i = 0; i <= n; i++) {
		printf("%d %d %d \n", a[i].row, a[i].column, a[i].value);
	}
}

void readMatrix(FILE* fp, Term a[]) {
	int i, row, col, temp, value, index = 1;
	Term element;
	//input row and column
	row = 0; col = 0; temp = 0; value = 0;
	if (!feof(fp)) fscanf(fp, "%d ", &row);
	if (!feof(fp)) fscanf(fp, "%d ", &col);

	//행마다 입력
	/*
	for row // for col
	만약 value = 0이면 입력받지 않는다.
	*/
	for (i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, " %d ", &temp);
			if (temp == EOF)break;
			if (!temp) continue;
			else {
				element.row = i;
				element.column = j;
				element.value = temp;
				a[index++] = element;
			}//else
		}//for j
	}//for i
	a[0].row = row;
	a[0].column = col;
	a[0].value = index - 1;
	
	//for debugging
	/*for (int i = 0; i < index; i++) {
		printf("%d\n", a[i].value);
	}*/
}//read Matrix


int COMPARE(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1; //x > y
}//compare

void storeSum(Term d[], int *totalD, int row, int column, int sum) {
	/* inf *sum != 0; then it along with its row and column
	position is stored as the *totalD+1 entry in d */

	if (sum)
		if (*totalD < MAX_TERMS) {
			d[++*totalD].row = row;
			d[*totalD].column = column;
			d[*totalD].value = sum;
			//*sum=0;
		}// if totalD
		else {
			fprintf(stderr, "numbers of terms in product exceeds %d\n", MAX_TERMS);
			exit(-1);
		}
}//if sum
