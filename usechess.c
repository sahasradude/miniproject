#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "setup_printchess.h"
#include "movechess.h"
#include "stack.h"
#include "attackchess.h"
void intro() { 
	int i;
	system("reset");
	system("setterm -cursor off");
	for(i = 0; i < 33; i++) {
		if(i%2 == 0)
			wprintf(L"%lc ", u_none);
		else
			wprintf(L"%lc ", u_none_black);
	}
	wprintf(L"\n");
	wprintf(L"\t\tC\n");
	wprintf(L"\n");
	sleep(1);
	wprintf(L"\t\t\tH\n");
	wprintf(L"\n");
	sleep(1);
	wprintf(L"\t\t\t\tE\n");
	wprintf(L"\n");
	sleep(1);
	wprintf(L"\t\t\t\t\tS\n");
	wprintf(L"\n");
	sleep(1);
	wprintf(L"\t\t\t\t\t\tS\n");
	for(i = 0; i < 33; i++) {
		if(i%2 == 0)
			wprintf(L"%lc ", u_none);
		else
			wprintf(L"%lc ", u_none_black);
	}
	wprintf(L"\n\n\n\n");
	sleep(1);
	wprintf(L"WELCOME TO CHESS.\n");
	wprintf(L"-TO QUIT, PRESS CTRL+D AS MOVE COORDINATES, OR Q or q\n");
	wprintf(L"-TO UNDO, PRESS U OR u AS MOVE COORDINATES\n"); 
	wprintf(L"-TO SAVE THE GIVEN BOARD TO A FILE, ENTER S or s AS MOVE COORDINATES\n");
	wprintf(L"(note: it is recommended that your terminal colour scheme is black and white)\n");
	sleep(8);
	system("clear");
	system("setterm -cursor on");
}
void outro() {
	//exit sequence
	system("reset");
	system("setterm -cursor off");
	wprintf(L"\n\n\n\n\n\n\n\t\t\t\t\tTHANK YOU FOR PLAYING!\n");
	sleep(3);
	system("reset");
	//end of exit sequence
}

int main() {
	setlocale(LC_ALL, "");
	//initialisations
	board b;
	board prev;
	stack st;
	init(&st);
	initboard(&b);
	setboard(&b);
	int prom;
	int i;
	int set = 0;
	char state = WHITE;
	coordinates s, d;
	int mv;
	int select;
	char filename[32];
	wchar_t source[16], dest[16];
	//end of initialisations
	intro(); //intro sequence
	wprintf(L"1. PRESS 1 FOR NEW GAME\n2. PRESS 2 TO LOAD GAME\n3. PRESS 3 FOR CREDITS\n4. PRESS 4 TO EXIT\n");
	wscanf(L"%d", &select);
	switch(select) {
		case 1:
			break;
		case 2:
			wprintf(L"enter filename:\n");
			wscanf(L"%s", filename);
			state = readfromfile(&b, filename);
			break;
		case 3:
			wprintf(L"CREATED BY DHRUVA SAHASRABUDHE, 111408051: IT-S3\n");
			exit(1);
		case 4:
			exit(1);
		default:
			wprintf(L"invalid choice\n");
			sleep(2);
			break;
	}
	system("reset");
	attacking_squares(&b, state == BLACK ? WHITE : BLACK);
	printboard(&b);
	push(&st, b);
	state == WHITE ? wprintf(L"WHITE TO PLAY\n") : wprintf(L"BLACK TO PLAY\n");
	while(1) {
		if(check(&b, state)) {
			if(checkmate(&b, state)){
				wprintf(L"CHECKMATE:\n");
				state == WHITE ? wprintf(L"BLACK WINS!\n") : wprintf(L"WHITE WINS!\n") ;
				sleep(5);
				break;
			}
			wprintf(L"CHECK!\n");
		}
		if(stalemate(&b, state)) {
			wprintf(L"STALEMATE! NO ONE WINS!\n");
			sleep(5);
			break;
		}
		wprintf(L"enter coordinates of piece to move:\n");
		if(wscanf(L"%ls", source) == -1)
			break;
		if(source[0] == L'q'|| source[0] == L'Q')
			break;
		if(source[0] == L'u'|| source[0] == L'U') {
			if(set == 0) //deals with extra pop arising in case of undo after check
				prev = pop(&st);
			set = 0;
			if(!empty(&st))  //current board has already been pushed and we need previous board so thats why we pop twice
				b = pop(&st);
			else {
				push(&st, prev);
				wprintf(L"nothing to undo\n");
				continue;
			}
			goto undo;
		}
		if(source[0] == L's'|| source[0] == L'S') {
			wprintf(L"enter filename\n");
			wscanf(L"%s", filename);
			savetofile(&b, state, filename);
			continue;
		}
		s = selectsquare(&b, source); //converts string to coordinates
		wprintf(L"enter coordinates of location to move to:\n");
		if(wscanf(L"%ls", dest) == -1)
			break;
		if(dest[0] == L'q'|| dest[0] == L'Q')
			break;
		if(dest[0] == L'u'|| dest[0] == L'U') {
			if(set == 0)
				prev = pop(&st); 
			set = 0;
			if(!empty(&st))
				b = pop(&st);
			else {
				push(&st, prev);
				wprintf(L"nothing to undo\n");
				continue;
			}
			goto undo;
		}	 
		if(dest[0] == L's'|| dest[0] == L'S') {
			wprintf(L"enter filename\n");
			wscanf(L"%s", filename);
			savetofile(&b, state, filename);
			continue;
		}
		d = selectsquare(&b, dest); //converts string dest into coordinates
		if(s.row != -1 && s.column != -1 && d.row != -1 && d.column != -1) {
			mv = validmove(&b, s, d, state); //checks if player is making a valid move acc. to rules of chess
			if (!mv) {
				wprintf(L"this is not a valid move, please try again\n");
				continue;
			}
			mv = movepiece(&b, s, d); //moves piece to new location, updates board
			if (!mv) {
				wprintf(L"this is not a valid move, please try again\n");
				continue;
			}
			if(b.sq[d.row][d.column].piece == u_wp && d.row == c_8) { //for simplicity sake only promotion to queen is allowed. 
				wprintf(L"pawn promotion\n");
				b.sq[d.row][d.column].piece = u_wQ;
			}
			if(b.sq[d.row][d.column].piece == u_bp && d.row == c_1) {
				wprintf(L"pawn promotion\n");
				b.sq[d.row][d.column].piece = u_bQ;
			}
		}
		else	{
			wprintf(L"invalid square selected, please try again\n");
			continue;
		}
		attacking_squares(&b, state == BLACK ? WHITE : BLACK);
		if (check(&b, state)) {
			wprintf(L"there is a check that needs attention\n");
			set = 1; //deals with extra pop which happens if undo comes after a check (see code for undo)
			if(!empty(&st))
				b = pop(&st);
			prev = b;
			continue;
		}
undo:
		attacking_squares(&b, state);
		system("clear");
		printboard(&b);	
		push(&st, b);
		state = (state == WHITE) ? BLACK : WHITE;
		if (state == WHITE)
			wprintf(L"WHITE TO PLAY\n");
		else
			wprintf(L"BLACK TO PLAY\n");
	}
	outro();
	return 0;
}

