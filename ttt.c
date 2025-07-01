#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};
char current_player = 'X';

void draw_board(Display *d, Window w, GC gc);
void draw_moves(Display *d, Window w, GC gc);
int check_win(void);
int check_draw(void);
void switch_player(void);
void handle_click(int x, int y);
void reset_game(void);

void draw_board(Display *d, Window w, GC gc) {
    int s = DefaultScreen(d);
    XSetForeground(d, gc, BlackPixel(d, s));
    XDrawLine(d, w, gc, 66, 0, 66, 200);
    XDrawLine(d, w, gc, 133, 0, 133, 200);
    XDrawLine(d, w, gc, 0, 66, 200, 66);
    XDrawLine(d, w, gc, 0, 133, 200, 133);
}

void draw_moves(Display *d, Window w, GC gc) {
    int s = DefaultScreen(d);
    int i, j;
    XSetForeground(d, gc, BlackPixel(d, s));
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                XDrawLine(d, w, gc, j * 66 + 10, i * 66 + 10, (j + 1) * 66 - 10, (i + 1) * 66 - 10);
                XDrawLine(d, w, gc, (j + 1) * 66 - 10, i * 66 + 10, j * 66 + 10, (i + 1) * 66 - 10);
            } else if (board[i][j] == 'O') {
                XDrawArc(d, w, gc, j * 66 + 10, i * 66 + 10, 46, 46, 0, 360 * 64);
            }
        }
    }
}

int check_win(void) {
    int i;
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return 1;
    return 0;
}

int check_draw(void) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void switch_player(void) {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

void handle_click(int x, int y) {
    int row = y / 66;
    int col = x / 66;
    if (board[row][col] == ' ') {
        board[row][col] = current_player;
        if (check_win()) {
            printf("Player %c wins!\n", current_player);
            reset_game();
        } else if (check_draw()) {
            printf("It's a draw!\n");
            reset_game();
        } else {
            switch_player();
        }
    }
}

void reset_game(void) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';}
    }
    current_player = 'X';
}

int main(void) {
    Display *d;
    Window w;
    XEvent e;
    int s;
    GC gc;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
    gc = DefaultGC(d, s);
    XSelectInput(d, w, ExposureMask | KeyPressMask | ButtonPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            draw_board(d, w, gc);
            draw_moves(d, w, gc);
        }
        if (e.type == ButtonPress) {
            handle_click(e.xbutton.x, e.xbutton.y);
            draw_moves(d, w, gc);
            XClearWindow(d, w);
            draw_board(d, w, gc);
            draw_moves(d, w, gc);
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    return 0;
}

