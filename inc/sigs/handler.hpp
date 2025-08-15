#ifndef _EVENT_
#define _EVENT_

#include <vector>

#include "sigs.hpp"

typedef int (*proc_sig)(void*);

int proc_sig_send_error(void* user_data);
int proc_sig_send_resize(void* user_data);

int proc_sig_exit(void* user_data);
int proc_sig_error(void* user_data);
int proc_sig_cursor_up(void* user_data);
int proc_sig_cursor_down(void* user_data);
int proc_sig_cursor_left(void* user_data);
int proc_sig_cursor_right(void* user_data);
int proc_sig_offset_panel_up(void* user_data);
int proc_sig_offset_panel_down(void* user_data);
int proc_sig_offset_panel_left(void* user_data);
int proc_sig_offset_panel_right(void* user_data);
int proc_sig_change_workdir_up(void* user_data);
int proc_sig_change_workdir_down(void* user_data);
int proc_sig_change_panel(void* user_data);
int proc_sig_refresh_screen(void* user_data);
int proc_sig_resize_win(void* user_data);
int proc_sig_hor_separation(void* user_data);
int proc_sig_ver_separation(void* user_data);
int proc_sig_close_panel(void* user_data);
int proc_sig_refresh_cursor(void* user_data);

#endif
