#ifndef _GLOB_VARS_
#define _GLOB_VARS_

#include "panel/tree/tree.hpp"
#include "panel/settings_panel.hpp"

#include <queue>
#include <vector>

enum MODE {
    SETTINGS,
    NORMAL
};

typedef struct {
    WINDOW* back_buf;
    bool ex;
    std::queue<Error> q_err;
    yx cursor;

    Tree tree_panels;
    std::vector<Panel> buf_panels;
    SettingsPanel settings;

    int screen_height;
    int screen_width;

    int count_panels;
    int active_panel;
    int active_buf;

    int mode;
    bool mode_hard_cursor;
} AppState;

#endif
