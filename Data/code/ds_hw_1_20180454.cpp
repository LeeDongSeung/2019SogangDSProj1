#include <stdio.h> 
#include <stdlib.h> 
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024 
#define compare(x,y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)

void readMatrix(FILE* fp, Term d[]) {
	int row1, col1, t, cnt = 1;
	fscanf(fp, "%d", &row1);
	fscanf(fp, "%d", &col1);

	d[0].row = row1;
	d[0].column = col1;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			fscanf(fp, "%d", &t);
			if (t != 0) {
				d[cnt].row = i;
				d[cnt].column = j;
				d[cnt].value = t;
				cnt++;
			}

		}
	}
	d[0].value = cnt;
}

void printMatrix(Term a[]) {
	int n;
	n = a[0].value;
	for (int i = 0; i <= n;i++) {
		printf("%d  %d  %d", a[i].row, a[i].column, a[i].value);
		printf("\n");
	}
}

Term matrixAdd(Term a[], Term b[], Term c[]) {
	int i = 1;
	int aa = 1, bb = 1, cc = 0;
	c[0].row = a[0].row, c[0].column = a[0].column;
	while (1) {
		if (aa >= a[0].value && bb >= b[0].value) break;
		else if (aa < a[0].value && bb >= b[0].value) {
			c[i].row = a[aa].row;
			c[i].column = a[aa].column;
			c[i].value = a[aa].value;
			i++; cc++; aa++;
		}
		else if (aa >= a[0].value && bb < b[0].value) {
			c[i].row = b[bb].row;
			c[i].column = b[bb].column;
			c[i].value = b[bb].value;
			i++; cc++; bb++;
		}
		else {
			if (a[aa].row == b[bb].row) {
				if (a[aa].column == b[bb].column) {
					c[i].row = a[aa].row;
					c[i].column = a[aa].column;
					c[i].value = (a[aa].value + b[bb].value);
					i++; cc++; aa++; bb++;
				}
				else if (a[aa].column > b[bb].column) {
					c[i].row = b[bb].row;
					c[i].column = b[bb].column;
					c[i].value = b[bb].value;
					i++; cc++; bb++;
				}
				else  if (a[aa].column < b[bb].column) {
					c[i].row = a[aa].row;
					c[i].column = a[aa].column;
					c[i].value = a[aa].value;
					i++; cc++; aa++;
				}
			}
			else if (a[aa].row > b[bb].row) {
				c[i].row = b[bb].row;
				c[i].column = b[bb].column;
				c[i].value = b[bb].value;
				i++; cc++; bb++;
			}
			else if (a[aa].row < b[bb].row) {
				c[i].row = a[aa].row;
				c[i].column = a[aa].column;
				c[i].value = a[aa].value;
				i++; cc++; aa++;
			}
			else { aa++; bb++; }
		}
	}
	c[0].value = cc;

	return *c;
}

void main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE *fp = fopen("a[4].txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b[3].txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	*c = matrixAdd(a, b, c);
	printMatrix(c);

}