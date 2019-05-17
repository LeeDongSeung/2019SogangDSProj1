/*
자구프로젝트 ONE
20181696
최재준
2019.5.03
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
void printMatrix(Term a[]);

int main() {
	Term a[MAX_TERMS] = { 0 }, b[MAX_TERMS] = { 0 }, c[MAX_TERMS] = { 0 };
	//created an array of TERMS and instasized it to zeros,, else 쓰래시값,, refer back to 기공설
	//also, zeros are safe due to the fact that no values in the matrix can be zeros (note: rows and cols can be)

	FILE *fp = fopen("A.txt", "r");
	if (fp == NULL) {
		printf("Error: File not found.");
		exit(1);
		//always check for fopen,, refer back to C Programming Winter course
	}
	readMatrix(fp, a);
	fclose(fp); //make sure to close,, refer back to C Programming Winter course

	fp = fopen("B.txt", "r");
	if (fp == NULL) {
		printf("Error: File not found.");
		exit(1);
		//always check for fopen
	}

	readMatrix(fp, b);
	fclose(fp); //make sure to close 

	//printMatrix(a);
	//printMatrix(b);

	matrixAdd(a, b, c);
	printMatrix(c);

	
	return 0;
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int aIndex = 0, bIndex = 0, cIndex = 0, i = 0;

	while (a[aIndex].value != 0 && b[bIndex].value != 0) {
		//printf("forever");
		while (a[aIndex].row == b[bIndex].row) {
			//printf("forever2");
			if (a[aIndex].column < b[bIndex].column) {
				c[cIndex].row = a[aIndex].row;
				c[cIndex].column = a[aIndex].column;
				c[cIndex].value = a[aIndex].value;
				aIndex++; cIndex++;
			}
			else if (a[aIndex].column > b[bIndex].column) {
				c[cIndex].row = b[bIndex].row;
				c[cIndex].column = b[bIndex].column;
				c[cIndex].value = b[bIndex].value;
				bIndex++; cIndex++;

			}
			else if (a[aIndex].row == b[bIndex].row && a[aIndex].column == b[bIndex].column) {
				c[cIndex].row = a[aIndex].row;
				c[cIndex].column = b[bIndex].column;
				c[cIndex].value = a[aIndex].value + b[bIndex].value;
				cIndex++; aIndex++; bIndex++;
			}
		}//end inner while

		if (a[aIndex].row != b[bIndex].row) {
			if (a[aIndex].row < b[bIndex].row) {
				c[cIndex].row = a[aIndex].row;
				c[cIndex].column = a[aIndex].column;
				c[cIndex].value = a[aIndex].value;
				aIndex++; cIndex++;

			}
			else if (a[aIndex].row > b[bIndex].row) {
				c[cIndex].row = b[bIndex].row;
				c[cIndex].column = b[bIndex].column;
				c[cIndex].value = b[bIndex].value;
				bIndex++; cIndex++;
			}
		}//end outer if
	}//end outer while
	cIndex--;
	//or else the while condition is offset,, even if one is found, it increments, which this decrementation is here for

	while (a[aIndex].value != 0) {
		c[cIndex].row = a[aIndex].row;
		c[cIndex].column = a[aIndex].column;
		c[cIndex].value = a[aIndex].value;
		

		aIndex++; cIndex++;
	}
	aIndex--;

	while (b[bIndex].value != 0) {

		c[cIndex].row = b[bIndex].row;
		c[cIndex].column = b[bIndex].column;
		c[cIndex].value = b[bIndex].value;
		

		bIndex++; cIndex++;
	}
	bIndex--;	
}//end function 

void readMatrix(FILE* fp, Term a[]) {
	int row, col, i, j, temp, counter = 0;

	fscanf(fp, "%d %d", &row, &col);
	//printf("ROW: %d COL: %d\n", row, col);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col;) {
			fscanf(fp, "%d", &temp);

			if (temp != 0) {
				a[counter].value = temp;
				a[counter].row = i;
				a[counter].column = j;
				counter++;
			}
			j++;
		}//end inner for       
	}//end outer for
}//end function

void printMatrix(Term a[]) {
	int i = 0, nterms = 0, maxRow = 0, maxCol = 0;
	
	while (a[i].value != 0) {
		if (a[i].row > maxRow) maxRow = a[i].row;
		if (a[i].column > maxCol) maxCol = a[i].column;
		nterms++; i++;
	}//end while

	printf("%d %d %d\n", maxRow+1, maxCol+1, nterms);
	//+1 to compenstate for arrays starting at index 0

	i = 0;
	while (a[i].value != 0) {
		printf("%d ", a[i].row);
		printf("%d ", a[i].column);
		printf("%d\n", a[i].value);
		i++;
	}//end while
}//end function