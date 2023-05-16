#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test_resetBoard(void **state)
{
	(void) state;

	int testBoard [8][8] = {{'R','N','B','Q','K','B','N','R'},
				 {'P','P','P','P','P','P','P','P'},
				 {' ',' ',' ',' ',' ',' ',' ',' '},
				 {' ',' ',' ',' ',' ',' ',' ',' '},
				 {' ',' ',' ',' ',' ',' ',' ',' '},
				 {' ',' ',' ',' ',' ',' ',' ',' '},
				 {'p','p','p','p','p','p','p','p'},
				 {'r','n','b','q','k','b','n','r'}};

	board_t board;
	resetBoard(board);

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			assert_int_equal(board[row][col], testBoard[row][col]);
		}
	}	
}
