#ifndef SETUP_PRINTCHESS_H
#define SETUP_PRINTCHESS_H
#include <wchar.h>
#include <locale.h>
enum {none = 0, wp, wN, wB, wR, wQ , wK, bp, bN, bB, bR, bQ, bK}; //values of all white and black pieces, along with value of no piece
enum {c_a = 2,c_b,c_c,c_d,c_e,c_f,c_g,c_h};//rank and file corresponding to array index sq[2][2] = a8, etc.
enum {c_8 = 2,c_7,c_6,c_5,c_4,c_3,c_2,c_1};
#define OFFBOARD 0
#define ONBOARD 1
#define OCCUPIED 2
#define W_CASTLE_SQ 4
#define B_CASTLE_SQ 8
#define ATTACKED 16
#define WHITE 1
#define BLACK 2
#define u_wp L'\x2659' //unicode for all the chess pieces and associated printable characters 
#define u_wN L'\x2658' 
#define u_wB L'\x2657' 
#define u_wR L'\x2656' 
#define u_wQ L'\x2655' 
#define u_wK L'\x2654' 
#define u_bp L'\x265F' 
#define u_bN L'\x265E' 
#define u_bB L'\x265D' 
#define u_bR L'\x265C' 
#define u_bQ L'\x265B' 
#define u_bK L'\x265A'
#define u_none L'\x25A1'
#define u_none_black L'\x25A0'
typedef struct coordinates {
        int row, column;
}coordinates;
typedef struct square {
	char info;
	wchar_t piece;
}square;
typedef struct board {
	square sq[12][12];
}board;
void initboard (board *b); //sets all squares to offboard or onboard, piece to none
void setboard (board *b); //sets up board in starting position
void printboard(board *b); //prints board
void savetofile(board *b, char player, char *filename);
char readfromfile(board *b, char *filename); //returns char indicating player
#endif
