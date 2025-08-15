#ifndef _GLOB_VARS_
#define _GLOB_VARS_

#include "panel/tree/tree.hpp"

#include <queue>

typedef struct {
    WINDOW* back_buf;
    bool ex;
    std::queue<Error> q_err;
    yx cursor;

    Tree tree_panels;
    std::vector<Panel> buf_panels;

    int screen_height;
    int screen_width;

    int count_panels;
    int active_panel;
} AppState;

#endif
