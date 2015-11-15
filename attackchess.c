/* This file is part of project.

    project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with project.  If not, see <http://www.gnu.org/licenses/>.*/



#include "attackchess.h"
//sees all the squares which all pieces of a particular player can attack
void attacking_squares(board *b, char player){
	// if player is white, for each white piece, see which squares it can move to.
	//go in board, store coordinates of each white piece, then pass that as source to a variant of validmove, and pass all other squares as destination. if there is a valid move to that square, then it is an attacking square for that piece. mark it so.
	int i, j;
	int p, q;
	coordinates s,d;
	board temp = *b;
	for(i = c_8; i <= c_1; i++) //sets all to non-attacked
		for(j = c_a; j <= c_h; j++)
			if(b->sq[i][j].info & ATTACKED)
				b->sq[i][j].info = (b->sq[i][j].info) - ATTACKED;

	if(player == WHITE) {
		for(i = c_8; i <= c_1; i++)
			for(j = c_a; j <= c_h; j++) {
				if(b->sq[i][j].piece >= u_wK &&	b->sq[i][j].piece <= u_wp) {
					if(b->sq[i][j].piece == u_wp) {
						/*pawns move differently to how they attack. so we cannot use the validmove function here
						as we do below*/
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
							/*if there is a valid move from one square to destination, 
							then that piece can attack the destination square for all 
							pieces other than pawn*/
							if(validmove(&temp,s,d,player))
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
						/*pawns move differently to how they attack. so we cannot use the validmove function here
						as we do below*/
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
							/*if there is a valid move from one square to destination, 
							then that piece can attack the destination square for all 
							pieces other than pawn*/
							if(validmove(&temp,s,d,player))
								b->sq[p][q].info = b->sq[p][q].info | ATTACKED;
						}
				}
			}
	}
}
coordinates kingfind(board *b, char player) { //locates the square on which the king is 
	int i, j;
	coordinates kingsq;
	kingsq.row = -1;
	kingsq.column = -1;
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
	return kingsq;
}
				

int check(board *b, char player) {
	//finds the king and then checks if his square is attacked by an enemy piece. if yes, then it is a check.
	coordinates kingsq;
	kingsq = kingfind(b, player);
	return (b->sq[kingsq.row][kingsq.column].info & ATTACKED);
}	
int checkmate(board *b, char player) {
	board btemp = *b;
	coordinates s, d;
	int i, j, p, q;
	if(!check(&btemp, player))
		return 0;
	/*there is a check. to see whether it is a checkmate, make every single possible valid move. if one particular valid move stops the 
	check, it is not a checkmate. if no such move exists, it is a checkmate.*/
	for(i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++)
			for(p = c_8; p <= c_1; p++)
				for(q = c_a; q <= c_h; q++) {
					s.row = i;
					s.column = j;
					d.row = p;
					d.column = q;
					if(validmove(&btemp, s, d, player)) {
						movepiece(&btemp, s, d); //move piece and update all attacked squares
						attacking_squares(&btemp, player == WHITE ? BLACK : WHITE);
						if(!check(&btemp, player)) {
							/*wprintf(L"this is btemp:\n");
							printboard(&btemp);*/
							return 0;
						}
					}
					btemp = *b;
				}
	return 1;
}
int stalemate (board *b, char player) {
	board btemp = *b;
	board btemp2;
	int i, j, p, q;
	coordinates s, d;
	//see all possible moves, for player, see all valid moves 
	for(i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++)
			for(p = c_8; p <= c_1; p++)
				for(q = c_a; q <= c_h; q++) {
					s.row = i;
					s.column = j;
					d.row = p;
					d.column = q;
					/*if there exists at least one legally valid move, 
					and if that valid move doesnt lead to a check, then it is a stalemate*/
					if(validmove(&btemp, s, d, player)) {
						btemp2 = btemp; 
						movepiece(&btemp2, s, d); //move piece and update all attacked squares
						attacking_squares(&btemp2, player == WHITE ? BLACK : WHITE);
						if(!check(&btemp2, player)) {
							/*wprintf(L"this is btemp:\n");
							printboard(&btemp2);*/
							return 0;
						}
					}
				}
	return 1; //1 will only be returned if there are no such valid moves for the player
}
//find the number of points for a given player and board
int pointcount(board *b, char player) { // knight/bishop = 3, rook = 5, queen = 8, pawn = 1
	int i, j;
	int points = 0;
	int queencount = 0;
	if (player == WHITE) {
		for(i = c_8; i <= c_1; i++)
			for(j = c_a; j <= c_h; j++) {
				if(b->sq[i][j].piece == u_wp)
					points++;
				else if(b->sq[i][j].piece == u_wN || b->sq[i][j].piece == u_wB)
					points = points + 3;
				else if(b->sq[i][j].piece == u_wR)
					points = points + 5;
				else if(b->sq[i][j].piece == u_wQ) {
					queencount++;
					if (queencount == 1) //pawn promotion to queen might cause two queens on the board
						points = points + 8;
					else
						points = points + queencount - 1;
				}
			}
	}
	else if (player == BLACK) {
		for(i = c_8; i <= c_1; i++)
			for(j = c_a; j <= c_h; j++) {
				if(b->sq[i][j].piece == u_bp)
					points++;
				else if(b->sq[i][j].piece == u_bN || b->sq[i][j].piece == u_bB)
					points = points + 3;
				else if(b->sq[i][j].piece == u_bR)
					points = points + 5;
				else if(b->sq[i][j].piece == u_bQ){
					queencount++;
					if (queencount == 1) //pawn promotion to queen might cause two or more queens on the board
						points = points + 8;
					else
						points = points + queencount - 1;
				}
			}
	}
	return 38 - points; /* max points = 2 * value of knight + 2 * value of bishop + 2 * value of rook + value of queen + 8 * value of pawn
			      = 4*3 + 2*5 + 8*1 + 8 
			      = 38. so points of pieces captured = 38 - total points on field*/
}


	
