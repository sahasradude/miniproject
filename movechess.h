#ifndef MOVECHESS_H
#define MOVECHESS_H
#include "setup_printchess.h"
coordinates selectsquare(board *b, wchar_t *move);
int movepiece(board *b, coordinates s, coordinates d);
int validmove(board *b, coordinates s, coordinates d, char player);
#endif
