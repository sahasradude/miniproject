#ifndef ATTACKCHESS_H
#define ATTACKCHESS_H
#include "movechess.h"
#include "setup_printchess.h"
void attacking_squares(board *b, char player);
int check(board *b, char player);
int checkmate(board *b, char player);
int stalemate(board *b, char player);
coordinates kingfind(board *b, char player);
int pointcount(board *b, char player);
#endif
