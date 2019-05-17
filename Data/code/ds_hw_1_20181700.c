#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row;
	int column;
	int value;
}Term;

#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main()
{
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

void readMatrix(FILE* fp, Term a[])
{
	fscanf(fp, "%d %d", &a[0].row , &a[0].column);
	
	int row = a[0].row;
	int col = a[0].column;

	int idx = 1;

	for(int i=0; i<row; i++)
		for (int j = 0; j < col; j++)
		{
			fscanf(fp, "%d", &a[idx].value);
			if (a[idx].value == 0)
				continue;

			a[idx].row = i;
			a[idx].column = j;
			idx++;
		}

	a[0].value = --idx; // idx �� 1���� �� �����̹Ƿ� -1 �� ���ش�.

}

void printMatrix(Term a[])
{
	for (int k = 0; k<=a[0].value ; k++)
		printf("%d %d %d \n", a[k].row, a[k].column, a[k].value);
	
}

void matrixAdd(Term a[], Term b[], Term c[])
{
	c[0].row = a[0].row;
	c[0].column = a[0].column;

	int a_idx = 1; // a �迭�� �ε��� ��
	int b_idx = 1; // b �迭�� �ε��� ��
	int c_idx = 1; // c �迭�� �ε��� ��

	int flag = 1;

	while (1)
	{
		if (a[a_idx].row == b[b_idx].row) // ���ǹ� 1 : a�� ��� b�� ���� ���� ��
		{
			if (a[a_idx].column == b[b_idx].column) // ���ǹ� 1-a : a�� ���� b�� ���� ���� ��
			{
				c[c_idx].row = a[a_idx].row;
				c[c_idx].column = a[a_idx].column;
				c[c_idx].value = a[a_idx].value + b[b_idx].value;
				c_idx++;
				a_idx++;
				b_idx++;

			}

			else if (a[a_idx].column < b[b_idx].column) // ���ǹ� 1-b : a�� �� < b�� ��
			{
				c[c_idx].row = a[a_idx].row;
				c[c_idx].column = a[a_idx].column;
				c[c_idx].value = a[a_idx].value;
				a_idx++;
				c_idx++;

			}

			else // ���ǹ� 1-c : a�� �� > b�� ��
			{
				c[c_idx].row = b[b_idx].row;
				c[c_idx].column = b[b_idx].column;
				c[c_idx].value = b[b_idx].value;
				b_idx++;
				c_idx++;
			}
		}

		else if (a[a_idx].row < b[b_idx].row) // ���ǹ� 2 : a�� �� < b�� ��
		{
			c[c_idx].row = a[a_idx].row;
			c[c_idx].column = a[a_idx].column;
			c[c_idx].value = a[a_idx].value;
			a_idx++;
			c_idx++;
		}

		else // ���ǹ� 3 : a�� �� > b�� ��
		{
			c[c_idx].row = b[b_idx].row;
			c[c_idx].column = b[b_idx].column;
			c[c_idx].value = b[b_idx].value;
			b_idx++;
			c_idx++;
		}


		if (a_idx - 1 == a[0].value) // Ż������ 1 : (a�� �ε��� �� - 1) �� a �������� ������ ������ ������ �� Ż��
			{
				flag = 0;
				--a_idx;
				break;
			}

		if (b_idx -1  == b[0].value) // Ż������ 2 : (b�� �ε��� �� - 1) �� b �������� ������ ������ ������ �� Ż��
			{
				flag = 1;
				--b_idx;
				break;
			}

	}


	if (flag == 0) // �����ִ� b ó��
	{
		while (b_idx <= b[0].value)
		{
			c[c_idx].row = b[b_idx].row;
			c[c_idx].column = b[b_idx].column;
			c[c_idx].value = b[b_idx].value;
			b_idx++;
			c[0].value =c_idx++;
		}

	}


	else // flag == 1 , �����ִ� a ó��
	{
		while (a_idx <= a[0].value)
		{
			c[c_idx].row = a[a_idx].row;
			c[c_idx].column = a[a_idx].column;
			c[c_idx].value = a[a_idx].value;
			a_idx++;
			c[0].value = c_idx++;
		}
	}


}



