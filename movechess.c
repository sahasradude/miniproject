#include "movechess.h"
#include "attackchess.h"
#include <math.h>
// N, R, K, Q, B, are pieces
//a1-h8 are moves
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
	 */ 
	//if a piece is in the way then that move cannot be made except for knight
	//if that square is under attack then king can't move there
	//if moving that piece causes a check, or if there is currently a check to my king
	int i, j, rvector, cvector;
	board btemp;
	coordinates rookmove_source, rookmove_dest;
	if(player == WHITE) {
		if(b->sq[d.row][d.column].piece >= u_wK && b->sq[d.row][d.column].piece <= u_wp) {
			return 0;
		}
		if (b->sq[s.row][s.column].piece == u_wN) {
			if(((d.row == s.row + 1 || d.row == s.row - 1) && (d.column == s.column + 2 || d.column == s.column - 2)) || ((d.row == s.row + 2 || d.row == s.row - 2) && (d.column == s.column + 1 || d.column == s.column - 1)))
				return 1;
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_wR) {
			if(d.row == s.row ^ d.column == s.column) {
				if(s.row == c_1 && s.column == c_a)
					if(b->sq[c_1][c_c].info & W_CASTLE_SQ) //castling not allowed after that particular rook moves. 
						b->sq[c_1][c_c].info = b->sq[c_1][c_c].info - W_CASTLE_SQ;
				if(s.row == c_1 && s.column == c_h)
					if(b->sq[c_1][c_g].info & W_CASTLE_SQ)
						b->sq[c_1][c_g].info = b->sq[c_1][c_g].info - W_CASTLE_SQ;
				if(d.row == s.row) {
					for (i = (d.column < s.column ? d.column: s.column) + 1 ; i < (d.column > s.column ? d.column: s.column); i++)
						if(b->sq[s.row][i].info & OCCUPIED)
							return 0;
				}
				else if(d.column == s.column) {
					for(i = (d.row < s.row ? d.row: s.row)+1; i < (d.row > s.row ? d.row: s.row); i++)
						if(b->sq[i][s.column].info & OCCUPIED)
							return 0;
				}
				return 1;
			}
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_wB) {
			if (d.row == s.row && d.column == s.column)
				return 0;
			if ((d.row - s.row == d.column - s.column) ||  (d.row - s.row == -(d.column - s.column))) {
				rvector = (d.row - s.row) / abs(d.row - s.row); 
				cvector = (d.column - s.column) / abs(d.row - s.row);
				i = s.row + rvector;
				j = s.column + cvector;
				while(i != d.row) {
					if(b->sq[i][j].info & OCCUPIED)
						return 0;
					i = i + rvector;
					j = j + cvector;
				}
				return 1;
			}
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_wp) {
			if(s.row == c_2) {
				if (((d.row == s.row - 1) && (d.column == s.column)) || ((d.row == s.row - 2) && (d.column == s.column))){ 
					if(b->sq[d.row][d.column].info & OCCUPIED)
						return 0; 
					return 1;
				}
				else if((d.row == s.row - 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_bK && b->sq[d.row][d.column].piece <= u_bp))
					return 1;
				else
					return 0;
			}
			else {
				if ((d.row == s.row - 1) && (d.column == s.column)){ 
					if(b->sq[d.row][d.column].info & OCCUPIED)
						return 0; 
					return 1;
				}
				else if((d.row == s.row - 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_bK && b->sq[d.row][d.column].piece <= u_bp))
					return 1;
				else
					return 0;
			}
		}
		else if(b->sq[s.row][s.column].piece == u_wQ) {
			if(d.row == s.row && d.column == s.column)
				return 0;
			if (d.row == s.row || d.column == s.column) {
				if(d.row == s.row) {
					for (i = (d.column < s.column ? d.column: s.column)+1 ; i < (d.column > s.column ? d.column: s.column); i++)
						if(b->sq[s.row][i].info & OCCUPIED)
							return 0;
				}
				else if(d.column == s.column) {
					for(i = (d.row < s.row ? d.row: s.row)+1; i < (d.row > s.row ? d.row: s.row); i++)
						if(b->sq[i][s.column].info & OCCUPIED)
							return 0;
				}
				else 
					return 1;
			}
			else if ((d.row - s.row == d.column - s.column) ||  (d.row - s.row == -(d.column - s.column))) {
				rvector = (d.row - s.row) / abs(d.row - s.row); 
				cvector = (d.column - s.column) / abs(d.row - s.row);
				i = s.row + rvector;
				j = s.column + cvector;
				while(i != d.row) {
					if(b->sq[i][j].info & OCCUPIED)
						return 0;
					i = i + rvector;
					j = j + cvector;
				}
				return 1;
			}
			else {
				return 0;
			}
		}
		else if(b->sq[s.row][s.column].piece == u_wK) {
			/*castling not possible if :
				king has moved
				rook has moved
				king under check
				if square between king and rook is occupied or attacked
				any square king moves to under attack*/
			if (d.row == s.row && d.column == s.column)
				return 0;
			if (b->sq[d.row][d.column].info & ATTACKED)
				return 0;
			if(b->sq[d.row][d.column].info & W_CASTLE_SQ) {
				if(check(b, player))
					return 0;
				//assert: king hasnt moved, rook hasnt moved.(taken care of elsewhere), not under check
				if(d.row == c_1 && d.column == c_c) {
					//check squares b1, c1, d1 for empty or occupied
					for (i = c_b; i <= c_d; i++)
						if((b->sq[c_1][i].info & OCCUPIED)||(b->sq[c_1][i].info & ATTACKED))
							return 0;
					rookmove_source.row = c_1;
					rookmove_source.column = c_a;
					rookmove_dest.row = c_1;
					rookmove_dest.column = c_d;
					movepiece(b, rookmove_source, rookmove_dest);
					return 1;
				}
				else if(d.row == c_1 && d.column == c_g) {
					//check f1, g1 
					for (i = c_f; i <= c_g; i++)
						if((b->sq[c_1][i].info & OCCUPIED)||(b->sq[c_1][i].info & ATTACKED))
							return 0;
					rookmove_source.row = c_1;
					rookmove_source.column = c_h;
					rookmove_dest.row = c_1;
					rookmove_dest.column = c_f;
					movepiece(b, rookmove_source, rookmove_dest);
					return 1; 
				}
				else
					return 0;
			}
			if((abs(s.row - d.row) <= 1) && (abs(s.column - d.column) <= 1)) { 
				if(b->sq[c_1][c_g].info & W_CASTLE_SQ)
					b->sq[c_1][c_g].info = b->sq[c_1][c_g].info - W_CASTLE_SQ; //if king moves, castle bit disabled
				if(b->sq[c_1][c_c].info & W_CASTLE_SQ)
					b->sq[c_1][c_c].info = b->sq[c_1][c_c].info - W_CASTLE_SQ;
				btemp = *b;
				movepiece(&btemp, s, d);
				if(check(&btemp, player))
					return 0;
				return 1;
			}
			else 
				return 0;
		}
		else {
			return 0;
		}
	}		
	else if(player == BLACK) { //lots of duplication of code here but theres no way around it
		if(b->sq[d.row][d.column].piece >= u_bK && b->sq[d.row][d.column].piece <= u_bp)
			return 0;
		if (b->sq[s.row][s.column].piece == u_bN) {
			if(((d.row == s.row + 1 || d.row == s.row - 1) && (d.column == s.column + 2 || d.column == s.column - 2)) || ((d.row == s.row + 2 || d.row == s.row - 2) && (d.column == s.column + 1 || d.column == s.column - 1)))
				return 1;
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_bR) {
			if(d.row == s.row ^ d.column == s.column) {
				if(s.row == c_8 && s.column == c_a)
					if(b->sq[c_8][c_c].info & B_CASTLE_SQ)
						b->sq[c_8][c_c].info = b->sq[c_8][c_c].info - B_CASTLE_SQ;
				if(s.row == c_8 && s.column == c_h)
					if(b->sq[c_8][c_g].info & B_CASTLE_SQ)
						b->sq[c_8][c_g].info = b->sq[c_8][c_g].info - B_CASTLE_SQ;
				if(d.row == s.row) {
					for (i = (d.column < s.column ? d.column: s.column)+1 ; i < (d.column > s.column ? d.column: s.column); i++)
						if(b->sq[s.row][i].info & OCCUPIED)
							return 0;
				}
				else if(d.column == s.column) {
					for(i = (d.row < s.row ? d.row: s.row)+1; i < (d.row > s.row ? d.row: s.row); i++)
						if(b->sq[i][s.column].info & OCCUPIED)
							return 0;
				}
				return 1;
			}
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_bB) {
			if (d.row == s.row && d.column == s.column)
				return 0;
			if ((d.row - s.row == d.column - s.column) ||  (d.row - s.row == -(d.column - s.column))) {
				rvector = (d.row - s.row) / abs(d.row - s.row); 
				cvector = (d.column - s.column) / abs(d.row - s.row);
				i = s.row + rvector;
				j = s.column + cvector;
				while(i != d.row) {
					if(b->sq[i][j].info & OCCUPIED)
						return 0;
					i = i + rvector;
					j = j + cvector;
				}
				return 1;
			}
			else
				return 0;
		}
		else if(b->sq[s.row][s.column].piece == u_bp) {
			if(s.row == c_7) {
				if(((d.row == s.row + 1) && (d.column == s.column)) || ((d.row == s.row + 2) && (d.column == s.column))){
					if(b->sq[d.row][d.column].info & OCCUPIED)
						return 0; 
					return 1;
				}
				else if((d.row == s.row + 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_wK && b->sq[d.row][d.column].piece <= u_wp))
					return 1;
				else
					return 0;
			}
			else {
				if ((d.row == s.row + 1) && (d.column == s.column)){ 
					if(b->sq[d.row][d.column].info & OCCUPIED)
						return 0; 
					return 1;
				}
				else if((d.row == s.row + 1 && (d.column == s.column + 1 || d.column == s.column - 1)) && (b->sq[d.row][d.column].piece >= u_wK && b->sq[d.row][d.column].piece <= u_wp))
					return 1;
				else
					return 0;
			}
		}
		else if(b->sq[s.row][s.column].piece == u_bQ) {
			if(d.row == s.row && d.column == s.column)
				return 0;
			if (d.row == s.row || d.column == s.column) {
				if(d.row == s.row) {
					for (i = (d.column < s.column ? d.column: s.column)+1 ; i < (d.column > s.column ? d.column: s.column); i++)
						if(b->sq[s.row][i].info & OCCUPIED)
							return 0;
				}
				else if(d.column == s.column) {
					for(i = (d.row < s.row ? d.row: s.row)+1; i < (d.row > s.row ? d.row: s.row); i++)
						if(b->sq[i][s.column].info & OCCUPIED)
							return 0;
				}
				else 
					return 1;
			}
			else if ((d.row - s.row == d.column - s.column) ||  (d.row - s.row == -(d.column - s.column))) {
				rvector = (d.row - s.row) / abs(d.row - s.row); 
				cvector = (d.column - s.column) / abs(d.row - s.row);
				i = s.row + rvector;
				j = s.column + cvector;
				while(i != d.row) {
					if(b->sq[i][j].info & OCCUPIED)
						return 0;
					i = i + rvector;
					j = j + cvector;
				}
				return 1;
			}
			else {
				return 0;
			}
		}
		else if(b->sq[s.row][s.column].piece == u_bK) {
			/*castling not possible if :
				king has moved
				rook has moved
				king under check
				if square between king and rook is occupied or attacked
				any square king moves to under attack*/
			if (d.row == s.row && d.column == s.column)
				return 0;
			if (b->sq[d.row][d.column].info & ATTACKED)
				return 0;
			if(b->sq[d.row][d.column].info & B_CASTLE_SQ) {
				if(check(b, player))
					return 0;
				//assert: king hasnt moved, rook hasnt moved.(taken care of elsewhere), not under check
				if(d.row == c_8 && d.column == c_c) {
					//check squares b1, c1, d1 for empty or occupied
					for (i = c_b; i <= c_d; i++)
						if((b->sq[c_8][i].info & OCCUPIED)||(b->sq[c_8][i].info & ATTACKED))
							return 0;
					rookmove_source.row = c_8;
					rookmove_source.column = c_a;
					rookmove_dest.row = c_8;
					rookmove_dest.column = c_d;
					movepiece(b, rookmove_source, rookmove_dest);
					return 1;
				}
				else if(d.row == c_8 && d.column == c_g) {
					//check f1, g1 
					for (i = c_f; i <= c_g; i++)
						if((b->sq[c_8][i].info & OCCUPIED)||(b->sq[c_8][i].info & ATTACKED))
							return 0;
					rookmove_source.row = c_8;
					rookmove_source.column = c_h;
					rookmove_dest.row = c_8;
					rookmove_dest.column = c_f;
					movepiece(b, rookmove_source, rookmove_dest);
					return 1; 
				}
				else
					return 0;
			}
			if((abs(s.row - d.row) <= 1) && (abs(s.column - d.column) <= 1)) {
				if(b->sq[c_8][c_g].info & B_CASTLE_SQ)
					b->sq[c_8][c_g].info = b->sq[c_8][c_g].info - B_CASTLE_SQ; //if king moves, castle bit disabled
				if(b->sq[c_8][c_c].info & B_CASTLE_SQ)
					b->sq[c_8][c_c].info = b->sq[c_8][c_c].info - B_CASTLE_SQ;
				btemp = *b;
				movepiece(&btemp, s, d);
				if(check(&btemp, player))
					return 0;
				return 1;
			}
			else 
				return 0;
		}
		else {
			return 0;
		}
	}
}

coordinates selectsquare(board *b, wchar_t *move) { //finds coordinates of given move in terms of 12x12 array, input is wide string
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
		b->sq[s.row][s.column].piece = u_none;
		return 1;
	}

	else
		return 0;
}










