#ifndef TESTS_H
#define TESTS_H

void test_resetBoard(void **state);
void test_move(void **state);
void test_removePiece(void **state);
void test_parseChessNotation(void **state);
void test__move(void **state);
void test_isValidMove(void **state);
void test_getCheckStatus(void **state);
void test__checks(void **state);
void test__getPieceAt(void **state);
void test__setPieceAt(void **state);

#endif
