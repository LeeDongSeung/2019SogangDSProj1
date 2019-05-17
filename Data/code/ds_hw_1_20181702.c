#include <stdio.h>
#include <stdlib.h>
typedef struct { 
	int row, column, value;
} Term;
#define MAX_TERMS 1024

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main()
{
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];

	FILE *fp = fopen("a.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("b.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a,b,c);
//	printMatrix(a);printf("\n"); printMatrix(b);printf("\n");
	printMatrix(c);
	return 0;
} // main

void readMatrix(FILE* fp, Term a[])
{
	int n, m; // n과 m은 각각 20이하의 양의 정수
	int tmp, i=1;
	int j, k;
	int **arr;
	int cnt=0; // a[0].value가 될 값

	/*txt파일의 제일 첫줄 row와 column 값 읽어서 n과 m에 저장*/
	fscanf(fp, "%d %d", &n, &m);
	a[0].row = n;
	a[0].column = m;

	/*arr라는 2차원 배열 nXm의 크기로 동적할당*/
	arr = (int**)malloc(sizeof(int*)*n);
	for(int x=0 ; x<n ; x++)
		arr[x] = (int*)malloc(sizeof(int)*m);

	/*txt파일 내의 숫자들을 2차원 배열 arr에 저장*/
	for(int x=0 ; x<n ; x++) {
		for(int y=0 ; y<m ; y++) {
			fscanf(fp, "%d", &tmp);
			arr[x][y] = tmp;
		}
	}
	
	/*arr에 저장한 값들을 희소행렬 Term a[]에 저장*/
	for(j=0 ; j<n ; j++) {
		for(k=0 ; k<m ; k++) {
			if(arr[j][k] != 0) {
				a[i].row = j;
				a[i].column = k;
				a[i].value = arr[j][k];
				i++;
				cnt++;
			}	
		}
	}
	a[0].value = cnt;

} // readMatrix

void printMatrix(Term a[])
{
	printf("%d %d %d\n", a[0].row, a[0].column, a[0].value);
	for(int i=1 ; i<=a[0].value ; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
} // printMatrix

void matrixAdd(Term a[], Term b[], Term c[])
{
	if(a[0].row >= b[0].row)
		c[0].row = a[0].row;
	else
		c[0].row = b[0].row;

	if(a[0].column >= b[0].column)
		c[0].column = a[0].column;
	else
		c[0].column = b[0].column;

	c[0].value = a[0].value + b[0].value; // a와 b에서 더해질 것은 나중에 고려

	int i=1, j=1, k=1;
	int cnt=0; // cnt는 a와 b에서 더해질 것까지 고려한 c에서의 총 개수(=c[0].value)

	/*희소 행렬 덧셈 및 정렬*/
	while(1) {
		if((i==a[0].value+1) && (j!=b[0].value+1)) { cnt++;
			c[k].row = b[j].row;
			c[k].column = b[j].column;
			c[k].value = b[j].value;
			j++; k++;
		}
		else if((j==b[0].value+1) && (i!=a[0].value+1)) { cnt++;
			c[k].row = a[i].row;
			c[k].column = a[i].column;
			c[k].value = a[i].value;
			i++; k++;
		}
		else if((i==a[0].value+1) && (j==b[0].value+1))
			break;
		else {
			if(a[i].row == b[j].row) {
				if(a[i].column == b[j].column) { cnt++;
					c[k].row = a[i].row;
					c[k].column = a[i].column;
					c[k].value = a[i].value + b[j].value;
					i++; j++; k++;
				}
				else if(a[i].column > b[j].column) { cnt++;
					c[k].row = b[j].row;
					c[k].column = b[j].column;
					c[k].value = b[j].value;
					j++; k++;
				}
				else if(a[i].column < b[j].column) { cnt++;
					c[k].row = a[i].row;
					c[k].column = a[i].column;
					c[k].value = a[i].value;
					i++; k++;
				}
			}
			else if(a[i].row > b[j].row) { cnt++;
				c[k].row = b[j].row;
				c[k].column = b[j].column;
				c[k].value = b[j].value;
				j++; k++;
			}
			else if(a[i].row < b[j].row) { cnt++;
				c[k].row = a[i].row;
				c[k].column = a[i].column;
				c[k].value = a[i].value;
				i++; k++;
			}
		}	
	} // while
	c[0].value = cnt; // cnt 값을 c[0].value에 대입
} // matrixAdd
