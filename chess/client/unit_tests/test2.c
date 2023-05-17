#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test_parseChessNotation(void **state)
{
	(void) state;
	
	int result = -1;
	int x_i, y_i, x_f, y_f;

	/* Knight Move */
	char * knight_moves[5] = {"b1c3", "g8f6", "e5d3", "d2b3", "f3h4"};
	int knight_expected[5][4] = {
    	{1, 7, 2, 5}, // b1 to c3
    	{6, 0, 5, 2}, // g8 to f6
    	{4, 3, 3, 4}, // e5 to d3
    	{3, 6, 1, 5}, // d2 to b3
    	{5, 5, 7, 4}  // f3 to h4
	};

	for (int i = 0; i < 5; i++)
	{
		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, KNIGHT_MOVE);
		assert_int_equal(x_i, knight_expected[i][0]);
		assert_int_equal(y_i, knight_expected[i][1]);
		assert_int_equal(x_f, knight_expected[i][2]);
		assert_int_equal(y_f, knight_expected[i][3]);
		
		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, KNIGHT_MOVE);
		assert_int_equal(x_i, knight_expected[i][0]);
		assert_int_equal(y_i, knight_expected[i][1]);
		assert_int_equal(x_f, knight_expected[i][2]);
		assert_int_equal(y_f, knight_expected[i][3]);
	}
	
	/* Bishop Move */	
	char * bishop_moves[5] = {"c1h6", "e4a8", "d7h3", "b2g7", "f3c6"};
	int bishop_expected[5][4] = {
    	{2, 7, 7, 2}, // c1 to h6
    	{4, 4, 0, 0}, // e4 to a8
    	{3, 1, 7, 5}, // d7 to h3
    	{1, 6, 6, 1}, // b2 to g7
    	{5, 5, 2, 2}  // f3 to c6
	};

	for (int i = 0; i < 5; i++)
	{
		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, BISHOP_MOVE);
		assert_int_equal(x_i, bishop_expected[i][0]);
		assert_int_equal(y_i, bishop_expected[i][1]);
		assert_int_equal(x_f, bishop_expected[i][2]);
		assert_int_equal(y_f, bishop_expected[i][3]);

		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);

		assert_int_equal(x_i, bishop_expected[i][0]);
		assert_int_equal(y_i, bishop_expected[i][1]);
		assert_int_equal(x_f, bishop_expected[i][2]);
		assert_int_equal(y_f, bishop_expected[i][3]);
		assert_int_equal(result, BISHOP_MOVE);
	}

	/* Rook Move */	
	char * rook_moves[5] = {"a1a5", "h1h6", "d3d7", "e2b2", "f3f7"};
	int rook_expected[5][4] = {
    	{0, 7, 0, 3}, // a1 to a5
    	{7, 7, 7, 2}, // h1 to h6
    	{3, 5, 3, 1}, // d3 to d7
    	{4, 6, 1, 6}, // e2 to b2
    	{5, 5, 5, 1}  // f3 to f7
	};	

	for (int i = 0; i < 5; i++)
	{
		result=_parseChessNotation(rook_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, ROOK_MOVE);
		assert_int_equal(x_i, rook_expected[i][0]);
		assert_int_equal(y_i, rook_expected[i][1]);
		assert_int_equal(x_f, rook_expected[i][2]);
		assert_int_equal(y_f, rook_expected[i][3]);

		result=_parseChessNotation(rook_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, ROOK_MOVE);
		assert_int_equal(x_i, rook_expected[i][0]);
		assert_int_equal(y_i, rook_expected[i][1]);
		assert_int_equal(x_f, rook_expected[i][2]);
		assert_int_equal(y_f, rook_expected[i][3]);
	}

	/* Queen Move */
	char * queen_moves[5] = {"d1d5", "h1e4", "b6f6", "e5b8", "f3c6"};
	int queen_expected[5][4] = {
    	{3, 7, 3, 3}, // d1 to d5
    	{7, 7, 4, 4}, // h1 to e4
    	{1, 2, 5, 2}, // b6 to f6
    	{4, 3, 1, 0}, // e5 to b8
    	{5, 5, 2, 2}  // f3 to c6
	};

	for (int i = 0; i < 5; i++)
	{
		result = _parseChessNotation(queen_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, QUEEN_MOVE);
		assert_int_equal(x_i, queen_expected[i][0]);
		assert_int_equal(y_i, queen_expected[i][1]);
		assert_int_equal(x_f, queen_expected[i][2]);
		assert_int_equal(y_f, queen_expected[i][3]);

		result = _parseChessNotation(queen_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, QUEEN_MOVE);
		assert_int_equal(x_i, queen_expected[i][0]);
		assert_int_equal(y_i, queen_expected[i][1]);
		assert_int_equal(x_f, queen_expected[i][2]);
		assert_int_equal(y_f, queen_expected[i][3]);
	}

	/* King Move */
	char * king_moves[5] = {"e1d2", "e1f2", "e1e2", "e1f1", "e1d1"};
	int king_expected[5][4] = {
	    {4, 7, 3, 6}, // e1 to d2
    	{4, 7, 5, 6}, // e1 to f2
    	{4, 7, 4, 6}, // e1 to e2
    	{4, 7, 5, 7}, // e1 to f1
    	{4, 7, 3, 7}  // e1 to d1
	};

	for (int i = 0; i < 5; i++)
	{
		result = _parseChessNotation(king_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, KING_MOVE);
		assert_int_equal(x_i, king_expected[i][0]);
		assert_int_equal(y_i, king_expected[i][1]);
		assert_int_equal(x_f, king_expected[i][2]);
		assert_int_equal(y_f, king_expected[i][3]);

		result = _parseChessNotation(king_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, KING_MOVE);
		assert_int_equal(x_i, king_expected[i][0]);
		assert_int_equal(y_i, king_expected[i][1]);
		assert_int_equal(x_f, king_expected[i][2]);
		assert_int_equal(y_f, king_expected[i][3]);
	}

	/* Long Castle */
	result=_parseChessNotation("O-O-O", &x_i, &y_i, &x_f, &y_f, WHITE);
	assert_int_equal(result, LONG_CASTLE);
	assert_int_equal(x_i, -1);
	assert_int_equal(y_i, -1;
	assert_int_equal(x_f, -1);
	assert_int_equal(y_f, -1);

	result=_parseChessNotation("O-O-O", &x_i, &y_i, &x_f, &y_f, BLACK);
	assert_int_equal(result, LONG_CASTLE);
	assert_int_equal(x_i, -1);
	assert_int_equal(y_i, -1);
	assert_int_equal(x_f, -1);
	assert_int_equal(y_f, -1);

	/* Short Castle */
	result=_parseChessNotation("O-O", &x_i, &y_i, &x_f, &y_f, WHITE);
	assert_int_equal(result, SHORT_CASTLE);
	assert_int_equal(x_i, -1);
	assert_int_equal(y_i, -1);
	assert_int_equal(x_f, -1);
	assert_int_equal(y_f, -1);

	result=_parseChessNotation("O-O", &x_i, &y_i, &x_f, &y_f, BLACK);
	assert_int_equal(result, SHORT_CASTLE);
	assert_int_equal(x_i, -1);
	assert_int_equal(y_i, -1);
	assert_int_equal(x_f, -1);
	assert_int_equal(y_f, -1);
}
