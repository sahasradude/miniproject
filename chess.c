#include <stdio.h>
#include "chess.h"
#include <wchar.h>
#include <locale.h>
void initboard (board *b) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++) {
			if ((i >=2 && i <=9) && (j >=2 && j <=9)) 
				b->sq[i][j].info = ONBOARD;
			else 
				b->sq[i][j].info = OFFBOARD;
		}
	}
}
void setboard (board *b) {
//assumes initialised
//change all occupied squares to occupied, 
// set pieces on occupied squares,
	int i,j;
	i = c_a;
	while(i<=c_h) { // sets white pawns;
		b->sq[c_2][i].piece = u_wp;
		b->sq[c_2][i].info = (b->sq[c_2][i].info) | OCCUPIED; // sets sq to occupied
		i++;
	}
	i = c_a;
	while(i<=c_h) { // sets black pawns;
		b->sq[c_7][i].piece = u_bp;
		b->sq[c_7][i].info = (b->sq[c_7][i].info) | OCCUPIED; // sets sq to occupied
		i++;
	}
	i = c_a;
	while(i <= c_h) {//sets both rooks
		if(i == c_a || i == c_h) {
			b->sq[c_1][i].piece = u_wR;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED; // sets sq to occupied
			b->sq[c_8][i].piece = u_bR;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED; // sets sq to occupied
		}
		if(i == c_b || i == c_g) { //sets both knights
			b->sq[c_1][i].piece = u_wN;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED; // sets sq to occupied
			b->sq[c_8][i].piece = u_bN;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED; // sets sq to occupied
		}
		if(i == c_c || i == c_f) { //sets both bishops
			b->sq[c_1][i].piece = u_wB;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED; // sets sq to occupied
			b->sq[c_8][i].piece = u_bB;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED; // sets sq to occupied
		}
		if(i == c_d) { //sets both queens
			b->sq[c_1][i].piece = u_wQ;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED; // sets sq to occupied
			b->sq[c_8][i].piece = u_bQ;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED; // sets sq to occupied
		}
		if(i == c_e) { //sets both kings
			b->sq[c_1][i].piece = u_wK;
			b->sq[c_1][i].info = (b->sq[c_1][i].info) | OCCUPIED; // sets sq to occupied
			b->sq[c_8][i].piece = u_bK;
			b->sq[c_8][i].info = (b->sq[c_8][i].info) | OCCUPIED; // sets sq to occupied
		}
		i++;



	}
}







void printboard(board *b) {
	int i, j;
	setlocale(LC_ALL, "");
	for (i = 0; i < 12; i++) {
		switch (i) {
			case 2:
				wprintf(L"%lc", u_8);
				break;
			case 3:
				wprintf(L"%lc", u_7);
				break;
			case 4:
				wprintf(L"%lc", u_6);
				break;
			case 5:
				wprintf(L"%lc", u_5);
				break;
			case 6:
				wprintf(L"%lc", u_4);
				break;
			case 7:
				wprintf(L"%lc", u_3);
				break;
			case 8:
				wprintf(L"%lc", u_2);
				break;
			case 9:
				wprintf(L"%lc", u_1);
				break;
			default:
				break;
		}
		for (j = 0; j < 12; j++) {
			if (b->sq[i][j].info & ONBOARD) {
				if (b->sq[i][j].info & OCCUPIED) {
					wprintf(L" %lc ", b->sq[i][j].piece);
				}
				else
					wprintf(L"%lc%lc%lc", u_space, u_none, u_space);

			}
			else 
				wprintf(L"%lc%lc%lc", u_space,u_space,u_space);
		}
		wprintf(L"%lc", u_nl);
	}
	wprintf(L"        %lc  %lc  %lc  %lc  %lc  %lc  %lc  %lc\n", u_a,u_b,u_c,u_d,u_e,u_f,u_g,u_h);
}
int main() {
	board b;
	initboard(&b);
	setboard(&b);
	printboard(&b);
	return 0;
}
