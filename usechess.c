#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "setup_printchess.h"
#include "movechess.h"
#include "stack.h"
#include "attackchess.h"
int main() {
	setlocale(LC_ALL, "");
	//initialisations
        board b;
	board prev;
	stack st;
	init(&st);
        initboard(&b);
        setboard(&b);
        int i;
	int set = 0;
	char state = WHITE;
	//end of initialisations
	//intro
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
	sleep(3);
        wprintf(L"WELCOME TO CHESS. TO QUIT, PRESS CTRL+D AS MOVE COORDINATES, OR Q or q\n");
        sleep(3);
        wprintf(L"TO UNDO, PRESS U OR u AS MOVE COORDINATES\n");
        sleep(4);
        system("clear");
	system("setterm -cursor on");
        //end of intro sequence
	attacking_squares(&b, state);
        printboard(&b);
	push(&st, b);
        coordinates s, d;
	int mv;
        wchar_t source[16], dest[16];
        wprintf(L"WHITE TO PLAY\n");
        while(1) {
		if(check(&b, state))
			wprintf(L"CHECK!\n");
                wprintf(L"enter coordinates of piece to move:\n");
                if(wscanf(L"%ls", source) == -1)
			break;
		if(source[0] == L'q'|| source[0] == L'Q')
			break;
		if(source[0] == L'u'|| source[0] == L'U') {
			if(set == 0) //deals with extra pop arising in case of undo after check
				prev = pop(&st);
			set = 0;
			if(!empty(&st))  //current board has already been pushed and we need previous board
				b = pop(&st);
			else {
				push(&st, prev);
				wprintf(L"nothing to undo\n");
				continue;
			}
			goto undo;
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
		}
		else	{
			wprintf(L"invalid square selected, please try again\n");
			continue;
		}
		attacking_squares(&b, state == BLACK ? WHITE : BLACK);
		if (check(&b, state)) {
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
	//exit sequence
        system("reset");
	system("setterm -cursor off");
        wprintf(L"\n\n\n\n\n\n\n\t\t\t\t\tTHANK YOU FOR PLAYING!\n");
        sleep(3);
        system("reset");
	//end of exit sequence
	return 0;
}

