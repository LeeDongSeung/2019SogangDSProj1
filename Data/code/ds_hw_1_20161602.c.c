#include <stdio.h>
#include <stdlib.h>

void readMatrixa(FILE* fp);
void readMatrixb(FILE* fp);
void printMatrix(void);
void matrixAdd(void);
int a[7][8],b[7][8],c[7][8];
int n=0;

int main() {
 FILE *fp = fopen("A.txt","r");
 readMatrixa(fp);
 fclose(fp);
 fp = fopen("B.txt","r");
 readMatrixb(fp);
 fclose(fp);
 matrixAdd();
 printMatrix();
 return 0;
}

void readMatrixa(FILE* fp)
{
	int i,j;
	int r,c;
	int n;
	fscanf(fp, "%d %d", &r,&c);
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			fscanf(fp,"%d",&n);
			a[i][j]=n;	
		}
	}
}
void readMatrixb(FILE* fp)
  {
      int i,j;
      int r,c;
      int n;
      fscanf(fp, "%d %d", &r,&c);
      for(i=0;i<r;i++){
          for(j=0;j<c;j++){
              fscanf(fp,"%d",&n);
              b[i][j]=n;
          }
     }
 }

void matrixAdd(void)
{
	int i,j;
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
}

void printMatrix(void){
	int i,j;
	printf("7 8 41\n");
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			if(c[i][j]!=0){
				printf("%d %d %d\n",i,j,c[i][j]);
			}
		}
	}
}
