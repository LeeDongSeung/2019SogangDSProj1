#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int row, col, value;
}Term;
#define MAX_TERMS 1024
Term k[MAX_TERMS];
int mat_a[MAX_TERMS][MAX_TERMS];
int mat_b[MAX_TERMS][MAX_TERMS];
int i,j;
int row_a;
int col_a;
int row_b;
int col_b;
int count=0;
int pos=0;

void insert(int col,int row,int value){
    k[pos].col = col;
    k[pos].row = row;
    k[pos].value = value;

    pos++;

}
//void readMatrix(FILE * fp,Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[],Term b[],Term c[],int mat[][MAX_TERMS]);
int main(){
    //쓸지 안쓸지 모름.
    Term a[MAX_TERMS],b[MAX_TERMS],c[MAX_TERMS];

    FILE* fp = fopen("A.txt","r");
    fscanf(fp,"%d %d",&row_a,&col_a);
    for(i=0;i<row_a;i++){
        for(j=0;j<col_a;j++){
            fscanf(fp,"%d",&mat_a[i][j]);
        }
    }

    //여기가 문제였음.
    int mat_c[MAX_TERMS][MAX_TERMS];
  //  readMatrix(fp,a);
    fclose(fp);


    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    fp=fopen("B.txt","r");
    fscanf(fp,"%d %d",&row_b,&col_b);
    for(i=0;i<row_b;i++){
        for(j=0;j<col_b;j++){
            fscanf(fp,"%d", &mat_b[i][j]);
        }
    }
    //readMatrix(fp,b);
    fclose(fp);

//    insert(row_a,col_a,0);
//    아래꺼 처럼 써야 transpose가 안됨. 
    insert(col_a,row_a,0);

    matrixAdd(a,b,c,mat_c);


    //TODO DEBUGGING 
   /* 
    for(i=0;i<row_a;i++){
        for(j=0;j<col_a;j++){
            printf("%d ",mat_c[i][j]);
        }
        printf("\n");
    }
    */
    
    //====> 디버깅을 해보니 mat_c에 들어간 값이 잘못되었음.
   //그렇다면 a나 b 텍스트의 값들이 잘못 받아졌을 수도 있음. 
    count =0;
    for(i=0;i<row_a;i++){
        for(j=0;j<col_a;j++){
            if(mat_c[i][j] ==0)
                continue;

            insert(j,i,mat_c[i][j]);
            count++;

        }
        k[0].value = count;
    }


    printMatrix(k);
    return 0;
}
void matrixAdd(Term a[],Term b[],Term c[],int mat[][MAX_TERMS]){
    for(i=0;i<row_a;i++){
        for(j=0;j<col_a;j++){
            mat[i][j]= mat_a[i][j] + mat_b[i][j];
        }
    }

}
void printMatrix(Term a[]){
    for(i=0;i<=a[0].value;i++)
        printf("%d %d %d\n",a[i].row,a[i].col,a[i].value);

}
