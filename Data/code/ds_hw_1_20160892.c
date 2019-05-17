#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef enum { head, entry } tagfield;
typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
}entry_node;

typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next; //head 
		entry_node entry; //entry
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];
 
matrix_pointer readMatrix(FILE* fps) {
	int numrows, numcols, numterms, numheads, i, j, a;
	int row, col, value, currentrow;
	matrix_pointer temp, last, node;
	FILE *fp = fopen("sparse.txt", "w");

	fscanf(fps, "%d %d", &numrows, &numcols);
	numheads = (numcols > numrows) ? numcols : numrows;

	numterms = 0;
	for (i = 0; i < numrows; i++) {
		for (j = 0; j < numcols; j++) {
			fscanf(fps, "%d", &a);
			if (a) {
				numterms++;
				fprintf(fp, "%d %d %d\n", i, j, a);
			}
		}
	}
	fclose(fp);

	fp = fopen("sparse.txt", "r");

	node = (matrix_pointer)malloc(sizeof(matrix_node));
	node->tag = entry;
	node->u.entry.row = numrows;
	node->u.entry.col = numcols;

	if (!numheads)
		node->right = node;
	else {
		for (i = 0; i < numheads; i++) {
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentrow = 0;
		last = hdnode[0];
		for (i = 0; i < numterms; i++) {
			fscanf(fp, "%d %d %d", &row, &col, &value);
			if (row > currentrow) {
				last->right = hdnode[currentrow];
				currentrow = row;
				last = hdnode[row];
			}
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;

			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}

		last->right = hdnode[currentrow];
		for (i = 0; i < numcols - 1; i++)
			hdnode[i]->u.next->down = hdnode[i + 1];

		//헤더노드 연결
		for (i = 0; i < numheads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numheads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	fclose(fp);
	return node;

}

void mwrite(matrix_pointer hdnode) {
	int i;
	if (hdnode != NULL)
	{
		matrix_pointer temp;
		matrix_pointer head;
		int non_zero = 0;

		head = hdnode->right;
		for (i = 0; i < (hdnode->u.entry.row); i++)
		{
			for (temp = head->right; temp != head; temp = temp->right)
				if (temp->u.entry.value != 0)
					non_zero++;
			head = head->u.next;
		}

		printf("\n%5d%5d%5d\n", hdnode->u.entry.row, hdnode->u.entry.col, non_zero);

		head = hdnode->right;
		for (i = 0; i < (hdnode->u.entry.row); i++)
		{
			for (temp = head->right; temp != head; temp = temp->right)
				printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
			head = head->u.next;
		}
	}
}

void merase(matrix_pointer* phdnode) {
	matrix_pointer x, y, head;
	int i, numhead;
	if (phdnode != NULL)
	{
		head = (*phdnode)->right;
		for (i = 0; i < (*phdnode)->u.entry.row; i++)
		{
			y = head->right;
			while (y != head)
			{
				x = y;
				y = y->right;
				free(x);
			}
			x = head;
			head = head->u.next;
			free(x);
		}
		y = head;
		while (y != *phdnode)
		{
			x = y;
			y = y->u.next;
			free(x);
		}
		free(*phdnode);
		*phdnode = NULL;
	}
}

matrix_pointer madd(matrix_pointer a, matrix_pointer b) {

	int numheads;
	int i, currentrow = 0;

	matrix_pointer result, temp, lasta, lastb, lastd;
	matrix_pointer lastha, lasthb;

	if ((a->u.entry.row != b->u.entry.row) || (a->u.entry.col != b->u.entry.col)) {
		printf("It cannot be added!\n");
		return;
	}

	else {
		result = (matrix_pointer)malloc(sizeof(matrix_node));
		result->tag = entry;
		result->u.entry.row = a->u.entry.row;
		result->u.entry.col = b->u.entry.col;

		numheads = (a->u.entry.col > a->u.entry.row) ? a->u.entry.col : a->u.entry.row;

		for (i = 0; i < numheads; i++) {
			temp = (matrix_pointer)malloc(sizeof(matrix_node));
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}

		lastd = hdnode[0];
		lasta = a->right->right;
		lastb = b->right->right;
		lastha = a->right;
		lasthb = b->right;

		do {
			if (lasta->u.entry.col > lastb->u.entry.col) {
				temp = (matrix_pointer)malloc(sizeof(matrix_node));
				temp->tag = entry;
				temp->u.entry.row = lastb->u.entry.row;
				temp->u.entry.col = lastb->u.entry.col;
				temp->u.entry.value = lastb->u.entry.value;
				lastd->right = temp;
				lastd = temp;
				lastb = lastb->right;
			}
			else if (lasta->u.entry.col < lastb->u.entry.col) {
				temp = (matrix_pointer)malloc(sizeof(matrix_node));
				temp->tag = entry;
				temp->u.entry.row = lasta->u.entry.row;
				temp->u.entry.col = lasta->u.entry.col;
				temp->u.entry.value = lasta->u.entry.value;
				lastd->right = temp;
				lastd = temp;
				lasta = lasta->right;
			}
			else if (lasta->u.entry.col == lastb->u.entry.col) {
				if (lasta->u.entry.value + lastb->u.entry.value != 0) {
					temp = (matrix_pointer)malloc(sizeof(matrix_node));
					temp->tag = entry;
					temp->u.entry.row = lasta->u.entry.row;
					temp->u.entry.col = lasta->u.entry.col;
					temp->u.entry.value = lasta->u.entry.value + lastb->u.entry.value;
					lastd->right = temp;
					lastd = temp;
				}
				lasta = lasta->right;
				lastb = lastb->right;
			}//last 옮기면서 더하기

			if ((lasta == lastha) && (lastb != lasthb)) {
				if (currentrow != (a->u.entry.row) - 1) {
					lastha = lastha->u.next;
					lasta = lastha->right;
				}
				if (lastb != lasthb) {
					while (lastb != lasthb) {
						temp = (matrix_pointer)malloc(sizeof(matrix_node));
						temp->tag = entry;
						temp->u.entry.row = lastb->u.entry.row;
						temp->u.entry.col = lastb->u.entry.col;
						temp->u.entry.value = lastb->u.entry.value;
						lastb = lastb->right;
						lastd->right = temp;
						lastd = temp;
					}
					if (currentrow != (b->u.entry.row) - 1) {
						lasthb = lasthb->u.next;
						lastb = lasthb->right;
					}
				}
				lastd->right = hdnode[currentrow];
				currentrow++;
				lastd = hdnode[currentrow];
			}

			else if ((lastb == lasthb) && (lasta != lastha)) {
				if (currentrow != (b->u.entry.row) - 1) {
					lasthb = lasthb->u.next;
					lastb = lasthb->right;
				}
				if (lasta != lastha) {
					while (lasta != lastha) {
						temp = (matrix_pointer)malloc(sizeof(matrix_node));
						temp->tag = entry;
						temp->u.entry.row = lasta->u.entry.row;
						temp->u.entry.col = lasta->u.entry.col;
						temp->u.entry.value = lasta->u.entry.value;
						lasta = lasta->right;
						lastd->right = temp;
						lastd = temp;
					}
					if (currentrow != (a->u.entry.row) - 1) {
						lastha = lastha->u.next;
						lasta = lastha->right;
					}
				}
				lastd->right = hdnode[currentrow];
				currentrow++;
				lastd = hdnode[currentrow];
			}

			else if ((lasta == lastha) && (lastb == lasthb)) {
				if (currentrow != (b->u.entry.row) - 1) {
					lastha = lastha->u.next;
					lasta = lastha->right;
					lasthb = lasthb->u.next;
					lastb = lasthb->right;
				}
				lastd->right = hdnode[currentrow];
				currentrow++;
				lastd = hdnode[currentrow];
			}

		} while (currentrow < (a->u.entry.row));
	}

	for (i = 0; i < a->u.entry.col - 1; i++)
		hdnode[i]->u.next->down = hdnode[i + 1];


	for (i = 0; i < numheads - 1; i++)
		hdnode[i]->u.next = hdnode[i + 1];
	hdnode[numheads - 1]->u.next = result;
	result->right = hdnode[0];

	return result;
}



void main()
{
	matrix_pointer a, b, d;
	FILE* fp1, *fp2;

	fp1 = fopen("A.txt", "r");
	fp2 = fopen("B.txt", "r");

	a = readMatrix(fp1);
	b = readMatrix(fp2);

	if (!(a->u.entry.row != b->u.entry.row || a->u.entry.col != b->u.entry.col)) {
		d = madd(a, b);
		mwrite(d);
		merase(&d);
	}
	else
		printf("It cannot be added!\n");

	merase(&a);
	merase(&b);
}