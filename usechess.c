#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "setup_printchess.h"
#include "movechess.h"
#include "stack.h"
#include "attackchess.h"
coordinates w_kingsq = {.row = c_1, .column = c_e};
coordinates b_kingsq = {.row = c_8, .column = c_e};
int main() {
	setlocale(LC_ALL, "");
        board b;
	board prev;
	stack st;
	init(&st);
        initboard(&b);
        setboard(&b);
        int i;
	char state = WHITE;
	system("clear");
	for(i = 0; i < 30; i++) {
		if(i%2 == 0)
			wprintf(L"%lc ", u_none);
		else
			wprintf(L"%lc ", u_none_black);
	}
	wprintf(L"\n");
	wprintf(L"\t\tC\n");
	sleep(1);
	wprintf(L"\t\t\tH\n");
	sleep(1);
	wprintf(L"\t\t\t\tE\n");
	sleep(1);
	wprintf(L"\t\t\t\t\tS\n");
	sleep(1);
	wprintf(L"\t\t\t\t\t\tS\n");
	for(i = 0; i < 30; i++) {
		if(i%2 == 0)
			wprintf(L"%lc ", u_none);
		else
			wprintf(L"%lc ", u_none_black);
	}
	wprintf(L"\n");
	sleep(3);
	system("clear");
        wprintf(L"WELCOME TO CHESS. TO QUIT, PRESS CTRL+D AS MOVE COORDINATES, OR Q or q\n");
        sleep(3);
        wprintf(L"TO UNDO, PRESS U OR u AS MOVE COORDINATES\n");
        sleep(4);
        system("clear");
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
			prev = pop(&st);
			if(!empty(&st))
				b = pop(&st);
			else {
				push(&st, prev);
				wprintf(L"nothing to undo\n");
				continue;
			}
			goto undo;
		}
                s = selectsquare(&b, source);
                wprintf(L"enter coordinates of location to move to:\n");
                if(wscanf(L"%ls", dest) == -1)
			break;
		if(dest[0] == L'q'|| dest[0] == L'Q')
			break;
		if(dest[0] == L'u'|| dest[0] == L'U') {
			prev = pop(&st);
			if(!empty(&st))
				b = pop(&st);
			else {
				push(&st, prev);
				wprintf(L"nothing to undo\n");
				continue;
			}
			goto undo;
		}	 
                d = selectsquare(&b, dest);
		if(s.row != -1 && s.column != -1 && d.row != -1 && d.column != -1) {
			mv = validmove(&b, s, d, state);
			if (!mv) {
				wprintf(L"this is not a valid move, please try again\n");
				continue;
			}
                	mv = movepiece(&b, s, d);
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
			wprintf(L"please clear the check\n");
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
	return 0;
}

