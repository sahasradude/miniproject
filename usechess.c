#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "movechess.h"
int main() {
	setlocale(LC_ALL, "");
        board b;
        initboard(&b);
        setboard(&b);
	char state = WHITE;
        wprintf(L"WELCOME TO CHESS. TO QUIT, PRESS CTRL+D AS MOVE COORDINATES\n");
        printboard(&b);
        coordinates s, d;
        int i = 0;
	int mv;
        wchar_t source[16], dest[16];
        wprintf(L"WHITE TO PLAY\n");
        while(1) {
                wprintf(L"enter coordinates of piece to move:\n");
                if(wscanf(L"%ls", source) == -1)
			break;
                s = selectsquare(&b, source);
                wprintf(L"enter coordinates of location to move to:\n");
                if(wscanf(L"%ls", dest) == -1)
			break;
                d = selectsquare(&b, dest);
		if(s.row != -1 && s.column != -1 && d.row != -1 && d.column != -1) {
			mv = validmove(&b, s, d, state);
			if (mv == 0) {
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
                printboard(&b);
                i++;
                if (i%2 == 0) {
			state = WHITE;
                        wprintf(L"WHITE TO PLAY\n");
		}
                else {
			state = BLACK;
                        wprintf(L"BLACK TO PLAY\n");
		}
        }
	return 0;
}

