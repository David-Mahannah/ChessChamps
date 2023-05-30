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
	resetBoard(b);
	/*
		** WHITE **
		Nb1c3 -> [1,0]->[2,2] : Valid
		Ng8f6 -> [6,7]->[5,5] : Invalid
		Nb1?? -> [1,0]->[-1,-1] : Invalid (Out of bounds)
		Nb1c3 -> [1,0]->[2,2] : Invalid (Invalid knight move)
		Nb1d2 -> [1,0]->[3,1] : Invalid (Move on top of other)
		Nd4b3 -> [3,3]->[1,2] : Invalid (Piece at x_i, y_i is not a knight) 
		** BLACK **
		Nb1c3 -> [1,0]->[2,2] : Invalid
		Ng8f6 -> [6,7]->[5,5] : Valid
		Nb1?? -> [1,0]->[-1,-1] : Invalid (Out of bounds)
		Nb1c3 -> [1,0]->[2,2] : Invalid (Invalid knight move)
		Nb1d2 -> [1,0]->[3,1] : Invalid (Move on top of other)
		Nd4b3 -> [3,3]->[1,2] : Invalid (Piece at x_i, y_i is not a knight) 


	*/
	/* Knight Move */
	int knight_coordinates[6][4] = {
    	{1, 0, 2, 2},   // b1 -> c3
    	{6, 7, 5, 5},   // g8 -> f6
    	{4, 4, -1, -1}, // b1 -> ??
    	{1, 0, 2, 2},   // b1 -> c3
    	{1, 0, 3, 1},   // b1 -> d2
    	{3, 3, 1, 2}    // d4 -> b3
	};

	int white_knight_expected_outputs[6] = {1,0,0,1,0,0};
	int black_knight_expected_outputs[6] = {0,1,0,0,0,0};
	for (int i = 0; i < 6; i++)
	{
		result = _isValidMove(b, knight_coordinates[i][0],
						knight_coordinates[i][1],
						knight_coordinates[i][2],
						knight_coordinates[i][3],
						KNIGHT_MOVE, WHITE);

		assert_int_equal(result, white_knight_expected_outputs[i]);

		
		result = _isValidMove(b, knight_coordinates[i][0],
						knight_coordinates[i][1],
						knight_coordinates[i][2],
						knight_coordinates[i][3],
						KNIGHT_MOVE, BLACK);

		assert_int_equal(result, black_knight_expected_outputs[i]);
	}
	
	/* Bishop Move */	
	/*
		** WHITE **
		b2b3  -> [1,1]->[1,2] : Valid Pawn move
		Bc1a3 -> [2,0]->[0,2] : Valid bishop
		
		Bc1a3 -> [2,0]->[0,2] : Invalid (Moves through pawn)
		Bc1?? -> [2,0]->[1,-1] : Invalid (bishop move)
		Ba3b4 -> [0,2]->[1,3]  : Invalid (Piece at x_i, y_i is not a knight)
		
		b7b6  -> [1,6]->[1,5] : Valid Pawn move
		Bc8a6 -> [2,7]->[0,5] : Valid bishop
		RESET
		Bc1a3 -> [2,7]->[0,5] : Invalid (Moves through pawn)
		Bc1?? -> [2,0]->[1,-1] : Invalid (bishop move)
		Ba3b4 -> [0,2]->[1,3]  : Invalid (Piece at x_i, y_i is not a knight)
		** BLACK **

	*/

	int bishop_coordinates[10][4] = {
    	{1, 1, 1, 2},   // b2 -> b3
    	{2, 0, 0, 2},   // c1 -> a3

		{2, 0, 0, 2},   // c1 -> a3
    	{2, 0, 1, -1},  // c1 -> ??
    	{0, 2, 1, 3},   // a3 -> b4

    	{1, 6, 1, 5},   // b7 -> b6
    	{2, 7, 0, 5},   // c8 -> a6

    	{2, 7, 0, 5},   // d4 -> b3
    	{2, 7, 1, 8},   // c8 -> ??
    	{0, 2, 1, 3},   // a3 -> b4
	};

	int white_bishop_expected_outputs[10] = {1,1,0,0,0,0,0,0,0,0};
	int black_bishop_expected_outputs[10] = {0,0,0,0,0,1,1,0,0,0};

	board_t black_board;
	board_t white_board;

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 10; i++)
	{

		if (i == 2 || i == 7)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		int move;
		if (i == 0 || i == 5)
		{
			move = PAWN_MOVE;
		} else {
			move = BISHOP_MOVE;
		}

		result = _isValidMove(white_board, bishop_coordinates[i][0],
						bishop_coordinates[i][1],
						bishop_coordinates[i][2],
						bishop_coordinates[i][3],
						move, WHITE);

		if (result == 1)
		{
			_move(white_board, bishop_coordinates[i][0],
					 bishop_coordinates[i][1],
					 bishop_coordinates[i][2],
					 bishop_coordinates[i][3]);
		}

		assert_int_equal(result, white_bishop_expected_outputs[i]);


		result = _isValidMove(black_board, bishop_coordinates[i][0],
						bishop_coordinates[i][1],
						bishop_coordinates[i][2],
						bishop_coordinates[i][3],
						move, BLACK);
		if (result == 1)
		{
			_move(black_board, bishop_coordinates[i][0],
				 			   bishop_coordinates[i][1],
				 			   bishop_coordinates[i][2],
				 			   bishop_coordinates[i][3]);
		}
		assert_int_equal(result, black_bishop_expected_outputs[i]);
	}



	/* Rook Move */	

	int rook_coordinates[10][4] = {
		{0, 0, 0, 2},   // c1 -> a3 (Invalid moves through pawn)
						// Remove pawn
    	{0, 0, 0, 2},   // a1 -> a3 Valid

		{7, 7, 7, 5},   // c8 -> a6
						// Remove pawn
    	{7, 7, 7, 5},   // a3 -> b4
	};

	int white_rook_expected_outputs[4] = {0,1,0,0};
	int black_rook_expected_outputs[4] = {0,0,0,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 4; i++)
	{
		if (i == 1)
		{
			// Remove A2 pawn
			black_board[6][0] = ' ';
			white_board[6][0] = ' ';
		}

		if (i == 3)
		{
			// Remove H7 pawn
			black_board[1][7] = ' ';
			white_board[1][7] = ' ';
		}

		int move;
		result = _isValidMove(white_board, rook_coordinates[i][0],
						rook_coordinates[i][1],
						rook_coordinates[i][2],
						rook_coordinates[i][3],
						ROOK_MOVE, WHITE);

		assert_int_equal(result, white_rook_expected_outputs[i]);

		result = _isValidMove(black_board, rook_coordinates[i][0],
						rook_coordinates[i][1],
						rook_coordinates[i][2],
						rook_coordinates[i][3],
						ROOK_MOVE, BLACK);

		assert_int_equal(result, black_rook_expected_outputs[i]);
	}

	/* Queen Move */

	int queen_coordinates[20][4] = {
		// WHITE
		// Rook-like moves
		{3, 0, 3, 2},   // d1 -> d3 (Invalid moves through pawn)
    	{3, 0, 3, 1},   // d1 -> d2 (Invalid moves onto pawn)
		{3, 1, 3, 3},	// Pawn moves up two
		{3, 0, 3, 2},	// d1 -> d3 (Valid)
		{3, 0, 3, 1},	// d1 -> d2 (valid)

		// Bishop-like moves
		{3, 0, 1, 2},   // d1 -> c2 (Invalid moves through pawn)
		{3, 0, 2, 1},	// d1 -> b3 (Invalid moves onto pawn)
		{2, 1, 2, 2},	// Pawn move up one
    	{3, 0, 1, 2},   // d1 -> c2 (Valid)
		{3, 0, 2, 1},	// d1 -> b3 (Valid)

		// BLACK
		// Rook-like moves
		{3, 7, 3, 5},   // d1 -> d3 (Invalid moves through pawn)
    	{3, 7, 3, 6},   // d1 -> d2 (Invalid moves onto pawn)
		{3, 6, 3, 4},	// Pawn moves up two
		{3, 7, 3, 5},	// d1 -> d3 (Valid)
		{3, 7, 3, 6},	// d1 -> d2 (valid)

		// Bishop-like moves
		{3, 7, 1, 5},   // d1 -> c2 (Invalid moves through pawn)
		{3, 7, 2, 6},	// d1 -> b3 (Invalid moves onto pawn)
		{2, 6, 2, 5},	// Pawn move up one
    	{3, 7, 1, 5},   // d1 -> c2 (Valid)
		{3, 7, 2, 6},	// d1 -> b3 (Valid)

	};

	int white_queen_expected_outputs[20] = {0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0};
	int black_queen_expected_outputs[20] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1};

	resetBoard(black_board);
	resetBoard(white_board);

	int move;

	for (int i = 0; i < 20; i++)
	{
		move = QUEEN_MOVE;
		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			move = PAWN_MOVE;
		}
	
		if (i == 10)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		result = _isValidMove(white_board, queen_coordinates[i][0],
										   queen_coordinates[i][1],
										   queen_coordinates[i][2],
										   queen_coordinates[i][3],
										   move, WHITE);

		assert_int_equal(result, white_queen_expected_outputs[i]);

		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			_move(white_board, queen_coordinates[i][0],
					 		   queen_coordinates[i][1],
					 		   queen_coordinates[i][2],
					 		   queen_coordinates[i][3]);
		}


		result = _isValidMove(black_board, queen_coordinates[i][0],
										   queen_coordinates[i][1],
										   queen_coordinates[i][2],
										   queen_coordinates[i][3],
										   move, BLACK);

		assert_int_equal(result, black_queen_expected_outputs[i]);
		
		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			_move(black_board, queen_coordinates[i][0],
					 queen_coordinates[i][1],
					 queen_coordinates[i][2],
					 queen_coordinates[i][3]);
		}
	}

	
	/* King Move */	
	int king_coordinates[8][4] = {
		// White
		{4, 0, 4, 1},   // e1 -> e2 (Invalid moves onto other piece)
    	{4, 0, 4, -1},   // e1 -> ?? (Invalid moves out of bounds)
						// Remove pawn
		{4, 0, 4, 1},   // e1 -> e2 (Valid)
    	{4, 1, 3, 2},   // e2 -> d3 (Valid)

		// Black
		{4, 7, 4, 6},   // c1 -> a3 (Invalid moves onto other piece)
    	{4, 7, 4, 8},   // a1 -> a3 (Invalid moves out of bounds)
						// Remove pawn
		{4, 7, 4, 6},   // c8 -> a6 (Valid)
    	{4, 6, 3, 5},   // a3 -> b4 (Valid)
	};

	int white_king_expected_outputs[8] = {0,0,1,1,0,0,0,0};
	int black_king_expected_outputs[8] = {0,0,0,0,0,0,1,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 8; i++)
	{
		if (i == 2)
		{
			white_board[6][4] = ' ';
		}

		if (i == 4)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 6)
		{
			black_board[1][4] = ' ';
		}

		result = _isValidMove(white_board, king_coordinates[i][0],
						king_coordinates[i][1],
						king_coordinates[i][2],
						king_coordinates[i][3],
						KING_MOVE, WHITE);

		assert_int_equal(result, white_king_expected_outputs[i]);

		result = _isValidMove(black_board, king_coordinates[i][0],
						king_coordinates[i][1],
						king_coordinates[i][2],
						king_coordinates[i][3],
						KING_MOVE, BLACK);

		assert_int_equal(result, black_king_expected_outputs[i]);
	}


	/* Long Castle */
	int long_castle_coordinates[4][4] = {
		// White
		{4, 0, 2, 0},   // e1 -> e2 (Invalid moves onto other piece)
						// Remove pawn
    	{4, 0, 2, 0},   // e2 -> d3 (Valid)

		// Black
		{4, 7, 2, 7},   // c1 -> a3 (Invalid moves onto other piece)
						// Remove pawn
    	{4, 7, 2, 7},   // a3 -> b4 (Valid)
	};

	int white_long_castle_expected_outputs[8] = {0,1,0,0};
	int black_long_castle_expected_outputs[8] = {0,0,0,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 4; i++)
	{
		if (i == 1)
		{
			white_board[7][1] = ' ';
			white_board[7][2] = ' ';
			white_board[7][3] = ' ';
		}

		if (i == 2)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 3)
		{
			black_board[0][1] = ' ';
			black_board[0][2] = ' ';
			black_board[0][3] = ' ';
		}

		result = _isValidMove(white_board, long_castle_coordinates[i][0],
						long_castle_coordinates[i][1],
						long_castle_coordinates[i][2],
						long_castle_coordinates[i][3],
						LONG_CASTLE, WHITE);

		assert_int_equal(result, white_long_castle_expected_outputs[i]);

		result = _isValidMove(black_board, long_castle_coordinates[i][0],
						long_castle_coordinates[i][1],
						long_castle_coordinates[i][2],
						long_castle_coordinates[i][3],
						LONG_CASTLE, BLACK);

		assert_int_equal(result, black_long_castle_expected_outputs[i]);
	}

	/* Short Castle */	
	int short_castle_coordinates[4][4] = {
		// White
		{4, 0, 6, 0},   // e1 -> e2 (Invalid moves onto other piece)
						// Remove pawn
    	{4, 0, 6, 0},   // e2 -> d3 (Valid)

		// Black
		{4, 7, 6, 7},   // c1 -> a3 (Invalid moves onto other piece)
						// Remove pawn
    	{4, 7, 6, 7},   // a3 -> b4 (Valid)
	};

	int white_short_castle_expected_outputs[8] = {0,1,0,0};
	int black_short_castle_expected_outputs[8] = {0,0,0,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 8; i++)
	{
		if (i == 1)
		{
			white_board[7][5] = ' ';
			white_board[7][6] = ' ';
		}

		if (i == 2)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 3)
		{
			black_board[0][5] = ' ';
			black_board[0][6] = ' ';
		}

		result = _isValidMove(white_board, short_castle_coordinates[i][0],
						short_castle_coordinates[i][1],
						short_castle_coordinates[i][2],
						short_castle_coordinates[i][3],
						SHORT_CASTLE, WHITE);

		assert_int_equal(result, white_short_castle_expected_outputs[i]);

		result = _isValidMove(black_board, short_castle_coordinates[i][0],
						short_castle_coordinates[i][1],
						short_castle_coordinates[i][2],
						short_castle_coordinates[i][3],
						SHORT_CASTLE, BLACK);

		assert_int_equal(result, black_short_castle_expected_outputs[i]);
	}


	/* Pawn move */
	int pawn_coordinates[12][4] = {
		// White
		{3, 1, 3, 3},   // d2 -> d4 (Valid)
    	{3, 3, 3, 4},	// d4 -> d5 (Valid)
		{3, 4, 3, 3},	// d5 -> d4 (Invalid moving backwards)
		{3, 4, 2, 5},	// d5 -> c6 (Invalid moving diagonal without attack)
		{3, 4, 3, 5},   // d5 -> d6 (Valid)
    	{3, 5, 2, 6},   // d6 -> c7 (Valid)

		// Black
		{3, 6, 3, 4},   // d7 -> d5 (Valid)
    	{3, 4, 3, 3},	// d5 -> d4 (Valid)
		{3, 3, 3, 4},	// d4 -> d5 (Invalid moving backwards)
		{3, 3, 2, 2},	// d4 -> c3 (Invalid moving diagonal without attack)
		{3, 3, 3, 2},   // d4 -> d3 (Valid)
    	{3, 2, 2, 1},   // d3 -> c2 (Valid)
	};

	int white_pawn_expected_outputs[16] = {1,1,0,0,1,1,0,0,0,0,0,0};
	int black_pawn_expected_outputs[16] = {0,0,0,0,0,0,1,1,0,0,1,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 16; i++)
	{
		if (i == 6)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}
		
		result = _isValidMove(white_board, pawn_coordinates[i][0],
						pawn_coordinates[i][1],
						pawn_coordinates[i][2],
						pawn_coordinates[i][3],
						PAWN_MOVE, WHITE);

		assert_int_equal(result, white_pawn_expected_outputs[i]);
		if (result == 1)
		{
			_move(white_board, pawn_coordinates[i][0],
					 pawn_coordinates[i][1],
					 pawn_coordinates[i][2],
					 pawn_coordinates[i][3]);
		}

		result = _isValidMove(black_board, pawn_coordinates[i][0],
						pawn_coordinates[i][1],
						pawn_coordinates[i][2],
						pawn_coordinates[i][3],
						PAWN_MOVE, BLACK);

		assert_int_equal(result, black_pawn_expected_outputs[i]);

		if (result == 1)
		{
			_move(black_board, pawn_coordinates[i][0],
					 pawn_coordinates[i][1],
					 pawn_coordinates[i][2],
					 pawn_coordinates[i][3]);
		}
	}
}
