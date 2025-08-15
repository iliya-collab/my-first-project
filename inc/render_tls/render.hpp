#ifndef _RENDER_
#define _RENDER_

#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <string>
#include <math.h>
#include <fstream>
#include <cstring>
#include <locale>
#include <codecvt>

std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& wstr);

#define STWS(str) s2ws((str))
#define WSST(wstr) ws2s((wstr))

#define LOGFILE "../logs.txt"
void clear_log();
void save_log(std::string msg);


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
