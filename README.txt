TITLE - 2 PLAYER CHESS

NAME - Dhruva Sahasrabudhe
MIS ID- 111408051

I have written a program which plays two player chess according to the standard rules of chess. The program has the following features:
1) moves are entered through keyboard, via board coordinates.
2) the pieces and board are displayed using unicode characters, and the program runs in the terminal itself, without ncurses. 
3) check, checkmate, stalemate are recognised
4) only valid moves are allowed to be played by the user. invalid moves give error.
5) there is functionality for castling, pawn-promotion however there is no functionality for en-passant because from a moral standpoint, i find en-passant to be a useless complication to the game. Also, for the sake of simplicity, pawn promotion to only queen is allowed, as the other pieces are rarely promoted anyway. 
6) there is undo functionality 
7) save and load functionality. (game can be saved to a user specified file at any time, by pressing s)
8) the points each side has accumulated are counted.
9) there is an intro and an outro sequence, along with a menu to select new game, load game, etc


NOTE: the files file1, file2, file3 etc are situations where the board is close to stalemate or checkmate, or pawn promotion for easier testing of these functions by examiner
