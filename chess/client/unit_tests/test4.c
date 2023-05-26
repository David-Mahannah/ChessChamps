#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test__move(void **state)
{
	(void) state;
	
	int result = -1;

	int moves[4][4] = {
		{2,1,2,2}, // c2 -> c3
		{3,0,3,6}, // d1 -> d7
		{1,7,2,5}, // b8 -> c6
		{7,7,7,0}, // h8 -> h1
	};

	int expected[4] = {'p','q','N','R'};
	char expected_takes[5] = {' ','P',' ','r'};

	board_t board;
	resetBoard(board);

	for (int i = 0; i < 4; i++)
	{

		result=_move(board, moves[i][0],
							moves[i][1],
							moves[i][2],
							moves[i][3]);
	
		assert_int_equal(result, expected_takes[i]);
		assert_int_equal(expected[i], board[7-moves[i][3]][moves[i][2]]);
	}
}
