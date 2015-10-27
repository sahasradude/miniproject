#include "setup_printchess.h"
typedef struct coordinates {
	int row, column;
}coordinates;
typedef struct node {
	board b;
	struct node next;
}node;
typedef struct stack {
	node *head;
	node *tail;
}stack;
coordinates selectsquare(board *b, wchar_t *move);
int movepiece(board *b, coordinates s, coordinates d);
int validmove(board *b, coordinates s, coordinates d, char player);
board *undo();
