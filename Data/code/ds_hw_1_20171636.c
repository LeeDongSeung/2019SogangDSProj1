#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
#define _CRT_SECURE_NO_WARNINGS

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int m, n, count=-1;
int count1, count2, size;

int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp = fopen("a[4].txt", "r");
	
	readMatrix(fp, a);
	count1 = count+1;
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	count = -1;
	readMatrix(fp, b);
	count2 = count+1;
	fclose(fp);

	matrixAdd(a, b, c);

	printMatrix(c);

	return 0;
}
void readMatrix(FILE* fp, Term a[]){
	int i,j,value;

	fscanf(fp, "%d %d\n", &m, &n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp, "%d", &value);
			if (value) {
				count++;
				a[count].value = value;
				a[count].row = i;
				a[count].column = j;
				
			}
		}
	}


}
void printMatrix(Term a[]){
	printf("%d %d %d\n", m, n, size);

	for (int i = 0; i < size; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}


}
void matrixAdd(Term a[], Term b[], Term c[]){

	int ca = 0, cb = 0, cc = 0;
	int i = 0;

	while (ca < count1&&cb < count2) {
		int inda = a[ca].row*n + a[ca].column;
		int indb = b[cb].row*n + b[cb].column;

		if (inda < indb) {
			c[cc++] = a[ca++];
		}
		else if (inda == indb) {
			if ((a[ca].value + b[cb].value != 0)) {
				c[cc].row = a[ca].row;
				c[cc].column = a[ca].column;
				c[cc++].value = a[ca++].value + b[cb++].value;
			}
		}
		else {
			c[cc++] = b[cb++];
		}
	}

			for (; ca < count1;)
				c[cc++] = a[ca++];
			for (; cb < count2;)
				c[cc++] = b[cb++];

			size = cc;
}
	