//#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	//printMatrix(a);
	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE *fp, Term a[]) {
	int n, m;
	fscanf(fp, "%d %d", &n, &m);
	int p = 1;
	a[0].row = n; a[0].column = m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int t;
			fscanf(fp, "%d", &t);
			if (t == 0) continue;
			a[p].row = i;
			a[p].column = j;
			a[p++].value = t;
		}
	a[0].value = p - 1;

}
void printMatrix(Term a[]) {
	for (int i = 0; i < a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int n = a[0].value + b[0].value;
	int count=0;
	int i = 1;
	int j = 1;
	int p = 1;

	while (n) {
		if (a[i].row == b[j].row && a[i].column == b[j].column) {
			c[p].row = a[i].row;
			c[p].column = a[i].column;
			c[p++].value = a[i].value + b[j].value;
			i++, j++;
			n--;
			count++;
		}
		else if (a[i].row == b[j].row && a[i].column < b[j].column) {
			c[p].row = a[i].row;
			c[p].column = a[i].column;
			c[p++].value = a[i].value;
			if (a[i + 1].row < 0) {
				a[i].row = a[i].row + 1;
			}
			else {
				i++;
			}
			count++;
		}
		else if (a[i].row == b[j].row && a[i].column > b[j].column) {
			c[p].row = b[j].row;
			c[p].column = b[j].column;
			c[p++].value = b[j].value;
			if (b[j + 1].row < 0) {
				b[j].row = b[j].row+1;
			}
			else {
				j++;
			}
			count++;
		}
		else if (a[i].row > b[j].row) {
			c[p].row = b[j].row;
			c[p].column = b[j].column;
			c[p++].value = b[j].value;
			if (b[j + 1].row < 0) {
				
			}
			else {
				j++;
			}
			count++;
		}
		else if (a[i].row < b[j].row) {
			c[p].row = a[i].row;
			c[p].column = a[i].column;
			c[p++].value = a[i].value;
			if (a[i + 1].row < 0) {
				
			}
			else {
				i++;
			}
			count++;
		}
		n--;
	}
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	c[0].value = count;

}
