#include <stdio.h>
#include "setup_printchess.h"
void initboard (board *b) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++) {
			if ((i >=c_a && i <= c_h) && (j >= c_8 && j <= c_1)) 
				b->sq[i][j].info = ONBOARD;
			else 
				b->sq[i][j].info = OFFBOARD;//these squares are here to prevent segfault when an onboard piece like eg knight 
							    //are being checked for valid move squares. having some buffer around board makes							    	    //things easier
		}
	}
}
void setboard (board *b) {
	//assumes initialised
	//change all occupied squares to occupied, 
	// set pieces on occupied squares,
	int i,j;
	for (j = c_8; j <= c_1; j++)
		for (i = c_a; i <= c_h; i++)
			b->sq[j][i].piece = u_none;
	i = c_a;
	while(i<=c_h) { // sets white pawns;
		b->sq[c_2][i].piece = u_wp;
		b->sq[c_2][i].info = (b->sq[c_2][i].info) | OCCUPIED;  
		i++;
	}
	i = c_a;
	while(i<=c_h) { // sets black pawns;
		b->sq[c_7][i].piece = u_bp;
		b->sq[c_7][i].info = (b->sq[c_7][i].info) | OCCUPIED;  
		i++;
	}
	i = c_a;
	while(i <= c_h) {//sets both rooks
		if(i == c_a || i == c_h) {
			b->sq[c_1][i].piece = u_wR;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED;  
			b->sq[c_8][i].piece = u_bR;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED;  
		}
		if(i == c_b || i == c_g) { //sets both knights
			b->sq[c_1][i].piece = u_wN;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED;  
			b->sq[c_8][i].piece = u_bN;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED;  
		}
		if(i == c_c || i == c_f) { //sets both bishops
			b->sq[c_1][i].piece = u_wB;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED;  
			b->sq[c_8][i].piece = u_bB;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED;  
		}
		if(i == c_d) { //sets both queens
			b->sq[c_1][i].piece = u_wQ;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED;  
			b->sq[c_8][i].piece = u_bQ;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED;  
		}
		if(i == c_e) { //sets both kings
			b->sq[c_1][i].piece = u_wK;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED;  
			b->sq[c_8][i].piece = u_bK;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED;
		}
		i++;
	} 
	//sets the castle bits for white and black. if these bits are enabled, castling can be done on the specified square
	b->sq[c_1][c_c].info = b->sq[c_1][c_c].info | W_CASTLE_SQ;
	b->sq[c_1][c_g].info = b->sq[c_1][c_g].info | W_CASTLE_SQ;
	b->sq[c_8][c_c].info = b->sq[c_8][c_c].info | B_CASTLE_SQ;
	b->sq[c_8][c_g].info = b->sq[c_8][c_g].info | B_CASTLE_SQ;
}
void printboard(board *b) { //prints the board
	int i, j;
	for (i = 0; i < 12; i++) {
		switch (i) {
			case 2:
				wprintf(L"8");
				break;
			case 3:
				wprintf(L"7");
				break;
			case 4:
				wprintf(L"6");
				break;
			case 5:
				wprintf(L"5");
				break;
			case 6:
				wprintf(L"4");
				break;
			case 7:
				wprintf(L"3");
				break;
			case 8:
				wprintf(L"2");
				break;
			case 9:
				wprintf(L"1");
				break;
			default:
				break;
		}
		for (j = 0; j < 12; j++) {
			if (b->sq[i][j].info & ONBOARD) {
					wprintf(L" %lc ", b->sq[i][j].piece);
			}
			else 
				wprintf(L"   ");
		}
		wprintf(L"\n");
	}
	wprintf(L"        a  b  c  d  e  f  g  h\n");
}
/*saves the board to a file
board will be stored in the following way: 
	first the player,
	then piece in a1, then info of a1 square,
	then piece in a2, then info of a2 square, 
	...and so on for all 64 squares, each on a new line.
*/
void savetofile(board *b, char player, char *filename) {
	int i, j;
	FILE *fp = fopen(filename, "w+");
	fwprintf(fp, L"%d",player);
	for(i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++) 
			fwprintf(fp, L"%lc%d",b->sq[i][j].piece, b->sq[i][j].info);
	fclose(fp);
}
//readfromfile modifies the given board to make it like board stored in file, and returns a char indicating the player to play
char readfromfile(board *b, char *filename) {
	int i, j;
	FILE *fp = fopen(filename, "r+");
	char player;
	fwscanf(fp, L"%d", &player);
	for(i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++) 
			fwscanf(fp, L"%lc%d",&b->sq[i][j].piece, &b->sq[i][j].info);
	fclose(fp);
	return player;
}










	
