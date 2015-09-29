#include <wchar.h>
#include <locale.h>

enum {none = 0, wp, wN, wB, wR, wQ , wK, bp, bN, bB, bR, bQ, bK}; //values of all white and black pieces, along with value of no piece
enum {c_a = 2,c_b,c_c,c_d,c_e,c_f,c_g,c_h};//rank and file corresponding to array index sq[2][2] = a8, etc.
enum {c_8 = 2,c_7,c_6,c_5,c_4,c_3,c_2,c_1};
#define OFFBOARD 0
#define ONBOARD 1
#define OCCUPIED 2
#define CASTLE_SQ 4
#define EN_PASSANT 8
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
#define u_space L'\x0020'
#define u_nl L'\x000A'
#define u_1 L'\x0031'
#define u_2 L'\x0032'
#define u_3 L'\x0033'
#define u_4 L'\x0034'
#define u_5 L'\x0035'
#define u_6 L'\x0036'
#define u_7 L'\x0037'
#define u_8 L'\x0038'
#define u_a L'\x0061'
#define u_b L'\x0062'
#define u_c L'\x0063'
#define u_d L'\x0064'
#define u_e L'\x0065'
#define u_f L'\x0066'
#define u_g L'\x0067'
#define u_h L'\x0068'
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
