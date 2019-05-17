#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	int row, column, value;
}Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE*fp = fopen("A.txt", "r");
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
	int i,temp,num_row,num_col;

	fscanf(fp, "%d %d\n", &num_row, &num_col);

	int p = num_row*num_col;
	a[0].row = num_row; a[0].column = num_col; a[0].value = p;

	for (i = 1; i <= p; i++)
	{
		if (i%num_col == 0)
		{
			fscanf(fp, "%d", &temp);
			a[i].row = i / num_col-1;
			a[i].column = num_col-1;
			a[i].value = temp;
		}//row�� ������ �迭���Ҹ� ���� ���� column�� ����� �ٸ����� �����Ͽ���.
		else
		{
			fscanf(fp, "%d", &temp);
			a[i].row = i / num_col;
			a[i].column = i % num_col - 1;
			a[i].value = temp;
		}
		
	}//�迭�� ������ n�̶�� �Ҷ� �ð����⵵��  O(n)�̴�.

}
void printMatrix(Term a[]) 
{
	int i,temp=a[0].value;
	int s = a[0].value;
	for (i = 1; i <= a[0].value; i++)
		if (a[i].value == 0)temp--;//value=0�� �迭�� ������ �����Ѵ�.
	
	a[0].value = temp;//���� ��µǴ� a[0].value�� ���� ���� �ٲپ��ش�.
	
	for (i = 0; i <= s; i++)
	{
		if (a[i].value != 0)
			printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}//value=0�� �迭�� ������� �������� ���������·� ����Ѵ�.
	//�迭�� ������ n�̶�� �Ҷ� �ð����⵵��  O(n)�̴�.
}
void matrixAdd(Term a[], Term b[], Term c[])
{
	c[0].column = a[0].column;
	c[0].row = a[0].row;
	int p=c[0].value = a[0].value;

	int i;

	for (i = 1; i <= p; i++)
	{
		c[i].row = a[i].row;
		c[i].column = a[i].column;
		c[i].value = a[i].value + b[i].value;
	}//row�� col�� ����  Term a���� ������ ����� �ּ�ȭ�Ͽ���.
	//�迭�� ������ n�̶�� �Ҷ� �ð����⵵��  O(n)�̴�.
	
}
