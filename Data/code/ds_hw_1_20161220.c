#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1024
#define COMPARE(x, y) ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1
typedef struct {
	int row;
	int col;
	int value;
}TERM;
void read_matrix(const char* file_name, TERM a[]);
void sum_matrix(TERM a[], TERM b[], TERM sum[]);
void print_matrix(TERM a[]);
int main() {
	TERM a[MAX_SIZE], b[MAX_SIZE], s[MAX_SIZE];
	read_matrix("a[4].txt", a);
	read_matrix("b[3].txt", b);
	sum_matrix(a, b, s);
	print_matrix(s);
	return 0;
}
void read_matrix(const char* file_name, TERM a[]) {
	int rows_num, cols_num, tmp, i, j, k = 0;
	FILE* file = fopen(file_name, "r");
	if (!file) {
		fprintf(stderr, "file is not opened successfully");
		exit(EXIT_FAILURE);
	}
	fscanf(file, "%d", &rows_num);
	fscanf(file, "%d", &cols_num);
	for (i = 0; i < rows_num; i++) {
		for (j = 0; j < cols_num; j++) {
			fscanf(file, "%d", &tmp);
			if (tmp) {
				a[++k].row = i;
				a[k].col = j;
				a[k].value = tmp;
			}
		}
	}
	a[0].row = rows_num;
	a[0].col = cols_num;
	a[0].value = k;
	fclose(file);
}
void sum_matrix(TERM a[], TERM b[], TERM sum[]) {
	int i, j, k, row_a, row_b, tmp;
	if (a[0].row != b[0].row || a[0].col != b[0].col) {
		fprintf(stderr, "not compatible size of matrices to add");
		exit(EXIT_FAILURE);
	}
	sum[0].row = a[0].row;
	sum[0].col = a[0].col;
	i = 1; j = 1; k = 0;
	while (i <= a[0].value && j <= b[0].value) {
		switch (COMPARE(a[i].row, b[j].row)) {
		case -1:
			row_a = a[i].row;
			for (; row_a == a[i].row; i++) {
				sum[++k].row = row_a;
				sum[k].col = a[i].col;
				sum[k].value = a[i].value;
			}
			break;
		case 0:
			switch (COMPARE(a[i].col, b[j].col)) {
			case -1:
				sum[++k].row = a[i].row;
				sum[k].col = a[i].col;
				sum[k].value = a[i++].value;
				break;
			case 0:
				if ((tmp = a[i].value + b[j].value)) {
					sum[++k].row = a[i].row;
					sum[k].col = a[i].col;
					sum[k].value = tmp;
				}
				i++; j++;
				break;
			case 1:
				sum[++k].row = b[j].row;
				sum[k].col = b[j].col;
				sum[k].value = b[j++].value;
				break;
			}
			break;
		case 1:
			row_b = b[j].row;
			for (; row_b == b[j].row; j++) {
				sum[++k].row = b[j].row;
				sum[k].col = b[j].col;
				sum[k].value = b[j].value;
			}
			break;
		}
	}
	//rest terms
	//just one of both below runs
	for (; i <= a[0].value; i++) {
		sum[++k].row = a[i].row;
		sum[k].col = a[i].col;
		sum[k].value = a[i].value;
	}
	for (; j <= b[0].value; j++) {
		sum[++k].row = b[j].row;
		sum[k].col = b[j].col;
		sum[k].value = b[j].value;
	}
	sum[0].value = k;
}
void print_matrix(TERM a[]) {
	int i;
	for (i = 0; i <= a[0].value; i++) {
		printf("%2d %2d %2d\n", a[i].row, a[i].col, a[i].value);
	}
}