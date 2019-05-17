#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int key;
} element;
typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
} stack;
typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
} queue;
stackPointer top;
queuePointer front, rear;

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int n1, n2;
	char c;
	top = NULL;
	front = NULL;
	rear = NULL;
	while (fscanf(fp, "%d", &n1) != EOF) {
		if (n1 == 0) {
			fscanf(fp, " %d\n", &n2);
			stackPointer Snode = (stackPointer)malloc(sizeof(stack));
			Snode->link = NULL;
			(Snode->data).key = n2;
			queuePointer Qnode = (queuePointer)malloc(sizeof(queue));
			Qnode->link = NULL;
			(Qnode->data).key = n2;
			if (top == NULL) {
				top = Snode;
			}else{
				Snode->link = top;
				top = Snode;
			}

			if (front == NULL) {
				front = Qnode;
				rear = Qnode;
			} else {
				rear->link = Qnode;
				rear = Qnode;
			}
		}
		else if (n1 == 1) {
			stackPointer Sdlt = top;
			queuePointer Qdlt = front;
			if (!Sdlt);
			else if (Sdlt) {
				top = Sdlt->link;
				free(Sdlt);
			}
			if (!Qdlt);
			else if (Qdlt) {
				front = Qdlt->link;
				free(Qdlt);
			}
		}
	}
		//
		stackPointer Stmp = top;
		queuePointer Qtmp = front;
		while (Stmp != NULL) {
			printf("%d ", (Stmp->data).key);
			Stmp = Stmp->link;
		}
		printf("\n");
		while (Qtmp != NULL) {
			printf("%d ", (Qtmp->data).key);
			Qtmp = Qtmp->link;
		}
		//
		stackPointer St = top;
		queuePointer Qt = front;
		while (St != NULL) {
			if (St) {
				top = St->link;
				free(St);
				St = top;
			}
		}
		while (Qt != NULL) {
			if (Qt) {
				front = Qt->link;
				free(Qt);
				Qt = front;
			}
		}
		return 0;
}