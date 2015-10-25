#include "setup_printchess.h"
typedef struct coordinates {
	int row, column;
}coordinates;
coordinates selectsquare(board *b, wchar_t *move);
int movepiece(board *b, coordinates s, coordinates d);
void validmove(board *b);

