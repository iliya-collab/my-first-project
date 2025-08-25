#ifndef _RENDER_
#define _RENDER_

#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <string>

std::string wstring_to_utf8(const std::wstring& str);
std::wstring utf8_to_wstring(const std::string& str);

#define s2ws(str) utf8_to_wstring((str))
#define ws2s(wstr) wstring_to_utf8((wstr))

typedef struct {
    int y;
    int x;
} yx;

typedef struct {
    yx spos;
    yx size;
} posPanel;

typedef struct {
    wchar_t sch;
    wchar_t lch;
    wchar_t ech;
} line;

typedef struct {
    wchar_t ls;     // левая сторона
    wchar_t rs;     // правая сторона
    wchar_t ts;     // верхняя сторона
    wchar_t bs;     // нижняя сторона
    wchar_t tl;     // левый верхний угол
    wchar_t tr;     // правый верхний угол
    wchar_t bl;     // левый нижний угол
    wchar_t br;     // правый нижний угол
} win_border;

void hor_line(WINDOW* win, yx spos, int width, line ln, short color_pair);

void ver_line(WINDOW* win, yx spos, int height, line ln, short color_pair);

void puts_str(WINDOW* win, yx spos, std::wstring str, short color_pair);

void puts_str_frame(WINDOW* win, yx spos, int x_end, std::wstring str, short color_pair);

void frame(WINDOW* win, win_border wb, posPanel pos_panel, short color_pair);

void clear_area(WINDOW* win, posPanel pos_panel, short color_pair);

#endif
