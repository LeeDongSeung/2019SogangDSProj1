#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
}Term;

#define MAX_TERMS 1024

void readMatrix(FILE *fp, Term a[]);

void printMatrix(Term a[]);

void matrixAdd(Term a[], Term b[], Term c[]);

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

void readMatrix(FILE *fp, Term a[]) {
	int i, j;
	int count_value = 0;
	int temp, temp_num_of_term = 1;

	fscanf(fp, "%d%d", &a[0].row, &a[0].column);

	for (i = 0; i < a[0].row; i++) {
		for (j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0)
				count_value++;
		}
	}

	a[0].value = count_value;

	fseek(fp, 0, SEEK_SET); // O.K 

	fscanf(fp, "%d%d", &a[0].row, &a[0].column);

	for (i = 0; i < a[0].row; i++) {
		for (j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0) {
				a[temp_num_of_term].row = i;
				a[temp_num_of_term].column = j;
				a[temp_num_of_term].value = temp;

				temp_num_of_term++;
			}
		}
	}
}

void printMatrix(Term a[]) {
	int i, num_of_terms;
	num_of_terms = a[0].value;

	for (i = 0; i <= num_of_terms; i++)
	{
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int numa = 1, numb = 1, numc = 1; // Term의 index 값 의미.
	int suma = 0, sumb = 0; // 각 행렬의 위치를 나타내는 수를 저장함.
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = 0;

	while (numa <= a[0].value && numb <= b[0].value) {
		suma = a[numa].row * a[0].column + a[numa].column;
		sumb = b[numb].row * b[0].column + b[numb].column;

		if (suma < sumb) {
			c[numc].row = a[numa].row;
			c[numc].column = a[numa].column;
			c[numc++].value = a[numa++].value;
		}
		else if (suma == sumb) {
			c[numc].row = a[numa].row;
			c[numc].column = a[numa].column;
			c[numc++].value = a[numa++].value + b[numb++].value;
		}
		else {
			c[numc].row = b[numb].row;
			c[numc].column = b[numb].column;
			c[numc++].value = b[numb++].value;
		}
	}

	for (; numa <= a[0].value; numa++) {
		c[numc].row = a[numa].row;
		c[numc].column = a[numa].column;
		c[numc++].value = a[numa].value;
	}
	for (; numb <= b[0].value; numb++) {
		c[numc].row = b[numb].row;
		c[numc].column = b[numb].column;
		c[numc++].value = b[numb].value;
	}
	c[0].value = numc - 1;
}