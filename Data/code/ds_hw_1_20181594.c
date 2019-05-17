#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]) {
	int cnt = 1;
	int temp;
	fscanf(fp, "%d %d\n", &a[0].row, &a[0].column);
	for (int i = 0;i<a[0].row;i++){
		for (int j = 0; j < a[0].column; j++) {
			fscanf(fp, "%d", &temp);
			if (temp != 0) {
				a[cnt].row = i;
				a[cnt].column = j;
				a[cnt].value = temp;
				cnt++;
			}
		}
	}
	a[0].value = cnt-1;
}
void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);

	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i;
	int acnt = 1, bcnt = 1;
	c[0].row = a[0].row;
	c[0].column = a[0].column;
	for (i = 1;;i++) {
		
		if (acnt > a[0].value && bcnt > b[0].value) break;
		if (a[acnt].row * a[0].column + a[acnt].column > b[bcnt].row * b[0].column + b[bcnt].column || acnt>a[0].value) {
			c[i].row = b[bcnt].row;
			c[i].column = b[bcnt].column;
			c[i].value = b[bcnt].value;
			bcnt++;
		}
		else if (a[acnt].row * a[0].column + a[acnt].column < b[bcnt].row * b[0].column + b[bcnt].column || bcnt>b[0].value) {
			c[i].row = a[acnt].row;
			c[i].column = a[acnt].column;
			c[i].value = a[acnt].value;
			acnt++;
		}
		else {
			c[i].row = a[acnt].row;
			c[i].column = a[acnt].column;
			c[i].value = a[acnt].value + b[bcnt].value;
			acnt++;
			bcnt++;
		}
	}
	
	c[0].value = i-1;
}
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