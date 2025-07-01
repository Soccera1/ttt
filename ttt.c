#include <X11/Xlib.h>
#include <stdio.h>

void draw_board(Display *d, Window w, GC gc) {
    int s = DefaultScreen(d);
    XSetForeground(d, gc, BlackPixel(d, s));

    // Draw vertical lines
    XDrawLine(d, w, gc, 66, 0, 66, 200);
    XDrawLine(d, w, gc, 133, 0, 133, 200);

    // Draw horizontal lines
    XDrawLine(d, w, gc, 0, 66, 200, 66);
    XDrawLine(d, w, gc, 0, 133, 200, 133);
}

int main() {
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
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            draw_board(d, w, gc);
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
    return 0;
}

