#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test_getCheckStatus(void **state)
{
	(void) state;
	
	int result = -1;

	board_t b;
	clearBoard(b);

	setPieceAt(b, B, 3, 'B');
	setPieceAt(b, E, 4, 'P');	
	setPieceAt(b, D, 7, 'Q');
	setPieceAt(b, D, 5, 'k');
	setPieceAt(b, C, 7, 'R');
	setPieceAt(b, B, 3, 'B');
	setPieceAt(b, E, 4, 'P');
	setPieceAt(b, E, 4, 'P');

	result = _getCheckStatus(b, WHITE);
	assert_int_equal(result, 1);

	clearBoard(b);

	setPieceAt(b, D, 5, 'k');

	result = _getCheckStatus(b, WHITE);
	assert_int_equal(result, 0);
}
