#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ROW 101
#define MAX_COL 101
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
	int row;
	int col;
	int val;
}Term;

Term* get_sparse(char* file_name) {
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("File open error!\n");
		exit(-1);
	}

	Term *a = (Term *)malloc(sizeof(Term) * 1);
	fscanf(fp, "%d %d", &a[0].row, &a[0].col); //행과 열의 개수를 받아둠


	int temp;
	int row = 0;
	int col = 0;
	int cur_size = 0; //현재 term a의 사이즈(0번째 인덱스 제외)
					  //printf("debug : %3d %3d %3d | %d\n", row, col, a[cur_size].val, cur_size);
	while (fscanf(fp, "%d", &temp) != EOF) {
		if (temp != 0) { //nonzero일떄 데이터 넣기
			cur_size++; //데이터 넣을거니까 size 갱신
			a = (Term*)realloc(a, sizeof(Term)*(cur_size + 1));
			a[cur_size].row = row;
			a[cur_size].col = col;
			a[cur_size].val = temp;
			//printf("debug : %3d %3d %3d | %d\n", row, col, a[cur_size].val, cur_size);
		}
		col++;
		if (col >= a[0].col) {//다음 인덱스를 이차원 인덱스로 변환시켜주는 과정
			col = 0;
			row++;
		}

	}
	a[0].val = cur_size;

	return a;
}

void print_sparse(Term *a) {
	int i;
	for (i = 0; i <= a[0].val; i++) {
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].val);
	}
}

Term *add_sparse(Term *a, Term *b) {
	Term *result = (Term*)malloc(sizeof(Term) * 1);
	
	int i = 1;//a의 인덱스
	int j = 1;//b의 인덱스 
	int r = 1;//result의 인덱스
	int temp_a, temp_b;//spars가 아닌 일반행렬에서의 인덱스로 환산
	
	while (i<=a[0].val || j<=b[0].val) {
		temp_a = a[i].row *a[0].col + a[i].col;
		temp_b = b[j].row *b[0].col + b[j].col;
		result = (Term*)realloc(result, sizeof(Term)*(r + 1));
		if ( (temp_a-temp_b)*(0.5 + a[0].val - i)*(0.5 + b[0].val - j) <= 0 ) {
			result[r].row = a[i].row;
			result[r].col = a[i].col;
			result[r].val = a[i].val;
			i++;
		}
		else if (temp_a == temp_b) {
			result[r].row = a[i].row;
			result[r].col = a[i].col;
			result[r].val = a[i].val + b[j].val;
			i++, j++;
		}
		else {
			result[r].row = b[j].row;
			result[r].col = b[j].col;
			result[r].val = b[j].val;
			j++;
		}
		r++;
	}
	//인덱스0의 값 정리
	result[0].row = MAX(a[0].row, b[0].row);
	result[0].col = MAX(a[0].col, b[0].col);
	result[0].val = r - 1; //마지막 while조건문후 더해진 1을 빼줌(sparse 는 마지막인덱스가 곧 크기임)
	
	return result;
}

int main() {
	Term* a = a = get_sparse("A.txt");
	Term* b = get_sparse("B.txt");
	print_sparse(add_sparse(a, b));

	return 0;
}