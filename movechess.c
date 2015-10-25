#include "movechess.h"
// N, R, K, Q, B, a-h, are pieces
//a1-h8 are moves  
void validmove(board *b);
coordinates selectsquare(board *b, wchar_t *move) { //finds coordinates of given move in terms of 12x12 array
	int i = 0;
	int j = 0;
	coordinates c;
	c.row = -1;
	c.column = -1;
	while(move[i] != L'\0') {
		if (move[i] >= L'a' && move[i] <= L'h') {
			j = i+1;
			while(move[j] != L'\0') {
				if (move[j] >= L'1' && move[j] <= L'8') {
					c.column = move[i] - L'a' + c_a;
					c.row = c_8 - move[j] + L'0' + 8;
				}
			j++;
			}
			
		}
		i++;
	}
	return c;
}
int movepiece(board *b, coordinates s, coordinates d) { // moves piece on coordinates to new location
	if (b->sq[s.row][s.column].info & OCCUPIED) {
		b->sq[s.row][s.column].info = b->sq[s.row][s.column].info - OCCUPIED;
		b->sq[d.row][d.column].info = b->sq[d.row][d.column].info | OCCUPIED;
		b->sq[d.row][d.column].piece = b->sq[s.row][s.column].piece;
		return 1;
	}

	else
		return 0;
}
	



					

					



