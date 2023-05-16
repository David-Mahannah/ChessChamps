#include <ncursesw/curses.h>
#include <locale.h>
#include <stddef.h>

int main() {
    setlocale(LC_ALL, "");   // Allow usage of extended characters
    initscr();               // Initialize the window
    start_color();           // Enable color change

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);    // Get the dimensions of the window

    int start_y = max_y / 2 - 4;       // Calculate the starting y-coordinate for the board
    int start_x = max_x / 2 - 8;       // Calculate the starting x-coordinate for the board

    // Unicode representations of chess pieces
    wchar_t *pieces[8] = {L"♖", L"♘", L"♗", L"♕", L"♔", L"♗", L"♘", L"♖"};
    wchar_t *pawns = L"♙";
    wchar_t *black_pieces[8] = {L"♜", L"♞", L"♝", L"♛", L"♚", L"♝", L"♞", L"♜"};
    wchar_t *black_pawns = L"♟︎";

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            attron(COLOR_PAIR((i + j) % 2 + 1));
            for(int x = 0; x < 2; ++x) {
                mvprintw(start_y + i, start_x + j * 2 + x, " ");
            }
            attroff(COLOR_PAIR((i + j) % 2 + 1));
        }
    }

    // Draw the pieces
    for(int i = 0; i < 8; ++i) {
        mvaddwstr(start_y, start_x + i * 2, pieces[i]);
        mvaddwstr(start_y + 1, start_x + i * 2, pawns);
        mvaddwstr(start_y + 6, start_x + i * 2, black_pawns);
        mvaddwstr(start_y + 7, start_x + i * 2, black_pieces[i]);
    }

    char text[100];
    mvprintw(start_y + 9, start_x - 4, "Enter your move: ");
    echo();                        // Enable echo
    getstr(text);                  // Get string from user
    noecho();                      // Disable echo

    mvprintw(start_y + 10, start_x - 4, "You entered: %s", text);

    refresh();              // Print it on to the real screen
    getch();                // Wait for user input
    endwin();               // End the window

    return 0;
}

