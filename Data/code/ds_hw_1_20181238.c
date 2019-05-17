#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]) {
		int n, m;
		fscanf(fp,"%d %d", &n, &m);
		int p = 1;
		
		a[0].row = n; a[0].column = m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				int t;
				fscanf(fp, "%d", &t);
				// printf("%d", t);
				if (t == 0) continue;
				a[p].row = i;
				a[p].column = j;
				a[p++].value = t;
			}
		a[0].value = p - 1;
		
	}


void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int idx=1;
	int value = 0;
	int ai=1, bi=1;
	c[0].row = a[0].row > b[0].row ? a[0].row : b[0].row;
	c[0].column = c[0].column > b[0].column ? a[0].column : b[0].column;	   	  
		while(ai<= a[0].value || bi<=b[0].value){
			if (a[ai].row == b[bi].row) {
				if (a[ai].column == b[bi].column) {
					c[idx].row = a[ai].row;
					c[idx].column = a[ai].column;
					c[idx].value = a[ai].value + b[bi].value;
					ai++; bi++; idx++; value++;
				}
				else if (a[ai].column < b[bi].column) { 
					c[idx].row = a[ai].row;
					c[idx].column = a[ai].column;
					c[idx].value = a[ai].value;
					ai++; idx++; value++;
				}
				else { 
					c[idx].row = b[bi].row;
					c[idx].column = b[bi].column;
					c[idx].value = b[bi].value;
					bi++; idx++; value++;
				}
			}
			else if (a[ai].row < b[bi].row || bi>b[0].value) {
				int temp = a[ai].row;
				while (a[ai].row == temp) {
					c[idx].row = a[ai].row;
					c[idx].column = a[ai].column;
					c[idx].value = a[ai].value;
					ai++; value++; idx++;
				}
				if (ai > a[0].value) break;
			}
			else if (a[ai].row > b[bi].row || ai>a[0].value) {
				int temp = b[bi].row;
				while (b[bi].row == temp) {
					c[idx].row = b[bi].row;
					c[idx].column = b[bi].column;
					c[idx].value = b[bi].value;
					bi++; value++; idx++;
				}
				if (ai > a[0].value) break;
			}
		}
		
			
	c[0].value = value;
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
