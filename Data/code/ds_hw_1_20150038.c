#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void readMatrix_ver2(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int compare(int x, int y);

int main(void) {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE* fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);


	
	/* ver2 : brutal method·Î °è»ê 
	Term aa[MAX_TERMS], bb[MAX_TERMS], cc[MAX_TERMS];

	fp = fopen("A.txt", "r");
	readMatrix_ver2(fp, aa);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix_ver2(fp, bb);
	fclose(fp);

	cc[0].row = aa[0].row, cc[0].column = aa[0].column;
	int k = 1;
	for (int i = 1; i <= aa[0].row; i++) {
		for (int j = 1; j <= aa[0].column; j++) {
			cc[k].row = aa[k].row;
			cc[k].column = aa[k].column;
			cc[k].value = aa[k].value + bb[k].value;
			k++;
		}
	}
	cc[0].value = k;

	printf("matrix ver 2 : \n\n");
	for (int i = 0; i < cc[0].value; i++) {
		printf("%2d %2d %2d\n", cc[i].row, cc[i].column, cc[i].value);
	}
	*/
	return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	int temp, count = 0;
	for (int i = 1; i <= a[0].row; i++) {
		for (int j = 1; j <=  a[0].column; j++) {
			fscanf(fp, "%d", &temp);
			if (temp) {
				count++;

				a[count].row = i;
				a[count].column = j;
				a[count].value = temp;
			}
		}
	}
	a[0].value = count;
}

void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) 
		printf("%2d %2d %2d\n", a[i].row-1, a[i].column-1, a[i].value);
	
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int index_a = 1, index_b = 1;
	int count = 0;
	c[0].row = a[0].row, c[0].column = a[0].column;
	
	while (index_a <= a[0].value && index_b <= b[0].value) {
		
		if (a[index_a].row == b[index_b].row) {
			count++;
			switch (compare(a[index_a].column, b[index_b].column)) {
			case -1:
				c[count].row = a[index_a].row;
				c[count].column = a[index_a].column;
				c[count].value = a[index_a].value;
				index_a++; break;
			case 0:
				c[count].row = a[index_a].row;
				c[count].column = a[index_a].column;
				c[count].value = a[index_a].value + b[index_b].value;
				index_a++, index_b++;
				break;
			case 1: 
				c[count].row = b[index_b].row;
				c[count].column = b[index_b].column;
				c[count].value = b[index_b].value;
				index_b++;
			}
		}
		else if (a[index_a].row < b[index_b].row) {
			int row_index = a[index_a].row;
			while (a[index_a].row == row_index) {
				count++;
				c[count].row = a[index_a].row;
				c[count].column = a[index_a].column;
				c[count].value = a[index_a].value;
				index_a++;
			}
		}
		else {
			int row_index = b[index_b].row;
			while (b[index_b].row == row_index) {
				count++;
				c[count].row = b[index_b].row;
				c[count].column = b[index_b].column;
				c[count].value = b[index_b].value;
				index_b++;
			}
		}
	}

	for (; index_a <= a[0].value; index_a++) {
		count++;
		c[count].row = a[index_a].row;
		c[count].column = a[index_a].column;
		c[count].value = a[index_a].value;
	
	}
	for (; index_b <= b[0].value; index_b++) {
		count++;
		c[count].row = b[index_b].row;
		c[count].column = b[index_b].column;
		c[count].value = b[index_b].value;
	}
	c[0].value = count;
	return;
}


int compare(int x, int y) {
	if (x < y)
		return -1;
	else if (x == y)
		return 0;
	else return 1;
}

void readMatrix_ver2(FILE* fp, Term a[]) {
	fscanf(fp, "%d %d", &a[0].row, &a[0].column);
	int temp, count = 0;
	for (int i = 1; i <= a[0].row; i++) {
		for (int j = 1; j <= a[0].column; j++) {
			fscanf(fp, "%d", &temp);
				count++;

				a[count].row = i;
				a[count].column = j;
				a[count].value = temp;
		}
	}
	a[0].value = count;
}