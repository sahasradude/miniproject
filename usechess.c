#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "setup_printchess.h"
#include "movechess.h"
#include "stack.h"
int main() {
	setlocale(LC_ALL, "");
        board b;
	stack st;
	init(&st);
        initboard(&b);
        setboard(&b);
	char state = WHITE;
        wprintf(L"WELCOME TO CHESS. TO QUIT, PRESS CTRL+D AS MOVE COORDINATES\nTO UNDO, PRESS U OR u AS MOVE COORDINATES\n");
        printboard(&b);
	push(&st, b);
        coordinates s, d;
        int i = 0;
	int mv;
	int undocount = 0;
        wchar_t source[16], dest[16];
        wprintf(L"WHITE TO PLAY\n");
        while(1) {
                wprintf(L"enter coordinates of piece to move:\n");
                if(wscanf(L"%ls", source) == -1)
			break;
		if(source[0] == L'u'|| source[0] == L'U') {
			if(!empty(&st))
				b = pop(&st);
			else
				wprintf(L"nothing to undo\n");
			if (undocount == 0 && i == 1) {
			if(!empty(&st)) 
				b = pop(&st);
			else 
				wprintf(L"nothing to undo\n");
			}
			undocount = 1;
			goto undo;
		}
                s = selectsquare(&b, source);
                wprintf(L"enter coordinates of location to move to:\n");
                if(wscanf(L"%ls", dest) == -1)
			break;
		if(dest[0] == L'u'|| dest[0] == L'U') {
			if(!empty(&st))
				b = pop(&st);
			else
				wprintf(L"nothing to undo\n");
			if (undocount == 0 && i == 1) {
				if(!empty(&st)) 
					b = pop(&st);
				else 
					wprintf(L"nothing to undo\n");
			}
			undocount = 1;
			goto undo;
		}
		undocount = 0;	 
                d = selectsquare(&b, dest);
		if(s.row != -1 && s.column != -1 && d.row != -1 && d.column != -1) {
			mv = validmove(&b, s, d, state);
			if (!mv) {
				wprintf(L"this is not a valid move, please try again\n");
				continue;
			}
                	mv = movepiece(&b, s, d);
			if (!mv) {
				wprintf(L"the entered coordinates are not valid, please try again\n");
				continue;
			}
		}
		else	{
			wprintf(L"invalid square selected, please try again\n");
			continue;
		}
		push(&st, b);
		undo:
                printboard(&b);	
			state = (state == WHITE) ? BLACK : WHITE;
		if (state == WHITE)
			wprintf(L"WHITE TO PLAY\n");
		else
			wprintf(L"BLACK TO PLAY\n");
		i = 1;
        }
	return 0;
}

