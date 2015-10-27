#include "movechess.h"
#include <math.h>
// N, R, K, Q, B, a-h, are pieces
//a1-h8 are moves
void storepos(board b) {
	node * temp = (node *) malloc(sizeof(node));
	temp->b = b;
	temp->next = NULL;



void undo(node *head) {
	node *temp;
	  
int validmove(board *b, coordinates s, coordinates d, char player) {
	//receives the coordinates of the move and tells if it is a valid move
	//assert: source square has a piece, destination is a valid square 
	/*ways of moving: knight: i+-2, j+-1, i+-1, j+-2
rook: i is constant or j is constant
bishop: i++ and j-- ,i-- and j++, i-- and j--, i++ and j++;
queen: combination of rook and bishop
king: i-1 to i+1, and j - 1 to j+1 
pawn: j++ or if killing opportunity, then j++ i++ ot j++ i--, if first move then double move okay;
ie if pawn is on a-2 to h-2 for white

castling: if that particular castling square is enabled then do it
en passant: if that particular square is en passant then do it
	 */ 
	//if a piece is in the way then that move cannot be made except for knight
	//if that square is under attack then king can't move there
	//if moving that piece causes a check, or if there is currently a check to my king
	int i, j, rvector, cvector;
	if(player == WHITE) {
		if (b->sq[s.row][s.column].piece == u_wN) {
			if(((d.row == s.row + 1 || d.row == s.row - 1) && (d.column == s.column + 2 || d.column == s.column - 2)) || ((d.row == s.row + 2 || d.row == s.row - 2) && (d.column == s.column + 1 || d.column == s.column - 1)))
				return 1;
			else
				return 0;
		}
		if(b->sq[s.row][s.column].piece == u_wR) {
			if(d.row == s.row ^ d.column == s.column) {
				if(d.row == s.row) {
					for (i = (d.column < s.column ? d.column: s.column) ; i < (d.column > s.column ? d.column: s.column); i++)
						if(b->sq[s.row][i].info & OCCUPIED)
							return 0;
				}
				else if(d.column == s.column) {
					for(i = (d.row < s.row ? d.row: s.row); i < (d.row > s.row ? d.row: s.row); i++)
						if(b->sq[i][s.column].info & OCCUPIED)
							return 0;
				}
				return 1;
			}
			else
				return 0;
		}
		if(b->sq[s.row][s.column].piece == u_wB) {
			if (d.row == s.row && d.column == s.column)
				return 0;
			if ((d.row - s.row == d.column - s.column) ||  (d.row - s.row == -(d.column - s.column))) {
				rvector = (d.row - s.row) / abs(d.row - s.row); 
				cvector = (d.column - s.column) / abs(d.row - s.row);
				for(i = s.row + rvector; i != d.row; i = i + rvector)
					for(j = s.column + cvector; j != d.column; j = j + cvector)
						if(b->sq[i][j].info & OCCUPIED)
							return 0;
				return 1;
			}
			else
				return 0;
		}
		if(b->sq[s.row][s.column].piece == u_wp) {
			if(s.row == c_2) {
				if (((d.row == s.row - 1) && (d.column == s.column)) || ((d.row == s.row - 2) && (d.column == s.column))) 
					return 1;
				else if((d.row == s.row - 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_bK && b->sq[d.row][d.column].piece <= u_bp))
					return 1;
				else
					return 0;
			}
			else {
				if ((d.row == s.row - 1) && (d.column == s.column)) 
					return 1;
				else if((d.row == s.row - 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_bK && b->sq[d.row][d.column].piece <= u_bp))
					return 1;
				else
					return 0;
			}
		}
	}
}



int attacking_squares(board *b, char player);
// if player is white, for each white piece, see which squares it can move to.
//go in board, store coordinates of each white piece, then pass that as source to a variant of validmove, and pass all other squares as destination. if there is a valid move to that square, then it is an attacking square for that piece. mark it so.
int check_checkmate() {
	//every square an opposition piece is attacking is known, see all king moves, count no of free squares. if zero, and check, then checkmate.
}	

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










