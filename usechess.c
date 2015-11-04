#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "setup_printchess.h"
#include "movechess.h"
#include "stack.h"
#include "attackchess.h"
coordinates w_kingsq;
coordinates b_kingsq;
int main() {
	w_kingsq.row = c_1;
	w_kingsq.column = c_e;
	b_kingsq.row = c_8;
	b_kingsq.column = c_e;
	setlocale(LC_ALL, "");
        board b;
	board prev;
	stack st;
	init(&st);
        initboard(&b);
        setboard(&b);
	char state = WHITE;
        wprintf(L"WELCOME TO CHESS. TO QUIT, PRESS CTRL+D AS MOVE COORDINATES, OR Q or q\nTO UNDO, PRESS U OR u AS MOVE COORDINATES\n");
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
		undo:
		attacking_squares(&b, state);
		if (check(&b, state)) {
			wprintf(L"please clear the check\n");
			continue;
		}
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

