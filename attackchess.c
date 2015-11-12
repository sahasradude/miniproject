#include "attackchess.h"
void attacking_squares(board *b, char player){
	// if player is white, for each white piece, see which squares it can move to.
	//go in board, store coordinates of each white piece, then pass that as source to a variant of validmove, and pass all other squares as destination. if there is a valid move to that square, then it is an attacking square for that piece. mark it so.
	int i, j;
	int p, q;
	coordinates s,d;
	for(i = c_8; i <= c_1; i++) //sets all to non-attacked
		for(j = c_a; j <= c_h; j++)
			if(b->sq[i][j].info & ATTACKED)
				b->sq[i][j].info = (b->sq[i][j].info) - ATTACKED;

	if(player == WHITE) {
		for(i = c_8; i <= c_1; i++)
			for(j = c_a; j <= c_h; j++) {
				if(b->sq[i][j].piece >= u_wK &&	b->sq[i][j].piece <= u_wp) {
					if(b->sq[i][j].piece == u_wp) {
						b->sq[i - 1][j + 1].info = b->sq[i - 1][j + 1].info | ATTACKED;
						b->sq[i - 1][j - 1].info = b->sq[i - 1][j - 1].info | ATTACKED;
						continue;
					}
					s.row = i;
					s.column = j;
					for(p = c_8; p<= c_1; p++)
						for(q = c_a; q <= c_h; q++) {
							d.row = p; 
							d.column = q;
							if(validmove(b,s,d,player))
								b->sq[p][q].info = b->sq[p][q].info | ATTACKED;
						}
				}
			}
	}
	if(player == BLACK) {
		for(i = c_8; i <= c_1; i++)
			for(j = c_a; j <= c_h; j++) {
				if(b->sq[i][j].piece >= u_bK &&	b->sq[i][j].piece <= u_bp) {
					if(b->sq[i][j].piece == u_bp) {
						b->sq[i + 1][j + 1].info = b->sq[i + 1][j + 1].info | ATTACKED;
						b->sq[i + 1][j - 1].info = b->sq[i + 1][j - 1].info | ATTACKED;
						continue;
					}
					s.row = i;
					s.column = j;
					for(p = c_a; p<= c_h; p++)
						for(q = c_8; q <= c_1; q++) {
							d.row = p; 
							d.column = q;
							if(validmove(b,s,d,player))
								b->sq[p][q].info = b->sq[p][q].info | ATTACKED;
						}
				}
			}
	}
}
coordinates kingfind(board *b, char player) {
	int i, j;
	coordinates kingsq;
	if(player == WHITE) {
	for (i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++)
			if (b->sq[i][j].piece == u_wK) {
				kingsq.row = i;
				kingsq.column = j;
				return kingsq;
			}
	}
	else if(player == BLACK) {
	for (i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++)
			if (b->sq[i][j].piece == u_bK) {
				kingsq.row = i;
				kingsq.column = j;
				return kingsq;
			}
	}
}
				

int check(board *b, char player) {
	coordinates kingsq;
	kingsq = kingfind(b, player);
	//wprintf(L"KING SQUARE = %d %d\n", kingsq.row, kingsq.column);
	return (b->sq[kingsq.row][kingsq.column].info & ATTACKED);
}	

