#ifndef _EVENT_
#define _EVENT_

#include <vector>

#include "sigs.hpp"

typedef int (*_proc_sig_)(void*);

namespace proc_sig {

    int send_error(void* user_data);
    int send_resize(void* user_data);
    int exit(void* user_data);
    int error(void* user_data);
    int cursor_up(void* user_data);
    int cursor_down(void* user_data);
    int cursor_left(void* user_data);
    int cursor_right(void* user_data);
    int offset_panel_up(void* user_data);
    int offset_panel_down(void* user_data);
    int offset_panel_left(void* user_data);
    int offset_panel_right(void* user_data);
    int change_workdir_up(void* user_data);
    int change_workdir_down(void* user_data);
    int change_panel(void* user_data);
    int refresh_screen(void* user_data);
    int resize_win(void* user_data);
    int hor_separation(void* user_data);
    int ver_separation(void* user_data);
    int close_panel(void* user_data);
    int refresh_cursor(void* user_data);
    int move_buffer(void* user_data);

}
#endif
