#include <stdio.h>
#include <stdlib.h>

void cal(int A[20][20], int B[20][20], int height, int width, int* sum) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			A[i][j] = A[i][j] + B[i][j];
			if (A[i][j] != 0) *sum = *sum + 1;
		}
	}
}

int main() {
	int A[20][20], B[20][20];
	int height, width, i, j;
	FILE *fp;
	int sum = 0;

	fp = fopen("A.txt", "r");
	fscanf(fp, "%d %d", &height, &width);
	for (i = 0; i < height; i++) for (j = 0; j < width; j++) fscanf(fp, "%d", &A[i][j]);
	fclose(fp);

	fp = fopen("B.txt", "r");
	fscanf(fp, "%d %d", &height, &width);
	for (i = 0; i < height; i++) for (j = 0; j < width; j++) fscanf(fp, "%d", &B[i][j]);
	fclose(fp);

	cal(A, B, height, width, &sum);
	printf("%d %d %d\n", height, width, sum);
	for (i = 0; i < height; i++) for (j = 0; j < width; j++) if (A[i][j] != 0) printf("%d %d %d\n", i, j, A[i][j]);
}