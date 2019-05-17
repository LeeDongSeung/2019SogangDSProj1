#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row, column, value;
} Term;

#define MAX_TERMS 101

void readMatrix(FILE* fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[]);

int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("a.txt","r");
	readMatrix(fp,a);
	fclose(fp);
	
	fp = fopen("b.txt","r");
	readMatrix(fp,b);
	fclose(fp);
	
	matrixAdd(a,b,c);
	printMatrix(c);
	
	return 0;
}

void readMatrix(FILE* fp, Term a[]) { // ���� �� ����� �о���̴� �Լ� ����
	int k = 1, count = 0; // count�� ��� �� ��ҵ��� ���� �����̰�, ����ü ��� a�� 0��° �ε������� ���� �� ����� row�� col���� �����ϹǷ� k=1�� �����Ͽ� 1�� �ε������� ������ �ϰ��� �Ѵ�.
	fscanf(fp, "%d %d", &(a[0].row), &(a[0].column)); // ��� ���� ������ �ҷ����δ�.

	for (int i = 0; i < a[0].row; i++) { // �о���� row�� ������ŭ �� �ݺ����� �ݺ�
		for (int j = 0; j < a[0].column; j++) { //�о���� col�� ������ŭ �� �ݺ����� �ݺ�
			a[k].row = i; // row���� ����
			a[k].column = j; // col ���� ����
			fscanf(fp, "%d", &(a[k].value)); //���� �� ����� ���� �о ����ü ��� a�� k��° �׸� ����. (value���� �ش� ���� �����Ѵ�.)

			k++; // ����ü ��� a�� ���� ��� ä��� ���� k�� ������Ų��.
		}
	}
	return;
}

void printMatrix(Term a[])
{
	int row_terms[101];
	int i, j, num_cols = a[0].column, num_terms = a[0].value, temp = 0, store = 0;
	
	Term c_transpose[101];
	
	c_transpose[0].column = a[0].row;
	c_transpose[0].row = num_cols;
	c_transpose[0].value = num_terms;
	
	if (num_terms > 0) {
		for (i = 0; i < num_cols; i++) row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) row_terms[a[i].column]++;
		temp = row_terms[1];
		row_terms[1] = 1 + row_terms[0];
		row_terms[0] = 1;
		for (i = 2; i < num_cols; i++) {
			store = row_terms[i];
			row_terms[i] = temp + row_terms[i - 1];
			temp = store;
		}
		for (i = 1; i <= num_terms; i++) {
			j = row_terms[a[i].column]++;
			c_transpose[j].row = a[i].column;
			c_transpose[j].column = a[i].row;
			c_transpose[j].value = a[i].value;
		}	

	}
	for (int k = 1; k <= c_transpose[0].value; k++) {
		if (c_transpose[k].value == 0)
			continue; // value���� 0�̸� �н�
		printf("%d %d %d\n", c_transpose[k].row, c_transpose[k].column, c_transpose[k].value); //value ���� �����ϸ� ���
	}
	return;
}

void matrixAdd(Term a[],Term b[],Term c[])
{
	int k = 1;
	int cnt = 0;
	
	c[0].row = a[0].row;
	c[0].column = c[0].column;
	
	for (int i = 0; i < c[0].row; i++) { // �о���� row�� ������ŭ �� �ݺ����� �ݺ�
		for (int j = 0; j < c[0].column; j++) { //�о���� col�� ������ŭ �� �ݺ����� �ݺ�
			c[k].row = i; // row���� ����
			c[k].column = j; // col ���� ����
			c[k].value = a[k].value + b[k].value; // �� ����� ���� ��ǥ ���� �ջ��Ͽ� �����Ѵ�. 
			
			if (c[k].value != 0) // k��° value ���� 0�� �ƴ� ���
				cnt++; // 0�� �ƴ� ���� ������ üũ�ϴ� �������� c�� ���� 1 ������Ų��.
			
			k++; // ����ü ��� a�� ���� ��� ä��� ���� k�� ������Ų��.
		}
	}
	c[0].value = cnt;
	return;
}
