#include "sigs/event_handler.hpp"

int EventHandler::init(AppState* ptr_app)
{
    user_data = ptr_app;
    timeout(0);
    keypad(stdscr, true);
    return 0;
}

void EventHandler::init_table_sigs()
{
    table_proc = (proc_sig*)malloc(SIGS::END_SIGS * sizeof(proc_sig));
    
    table_proc[SIGS::SIG_EXIT]              = proc_sig_exit;
    table_proc[SIGS::SIG_ERROR]             = proc_sig_error;
    table_proc[SIGS::SIG_CURSOR_UP]         = proc_sig_cursor_up;
    table_proc[SIGS::SIG_CURSOR_DOWN]       = proc_sig_cursor_down;
    table_proc[SIGS::SIG_CURSOR_LEFT]       = proc_sig_cursor_left;
    table_proc[SIGS::SIG_CURSOR_RIGHT]      = proc_sig_cursor_right;
    table_proc[SIGS::SIG_REFRESH_SCREEN]    = proc_sig_refresh_screen;
    table_proc[SIGS::SIG_RESIZE_WIN]        = proc_sig_resize_win;
    table_proc[SIGS::SIG_CHANGE_PANEL]      = proc_sig_change_panel;
    table_proc[SIGS::SIG_HOR_SEPARATION]    = proc_sig_hor_separation;
    table_proc[SIGS::SIG_VER_SEPARATION]    = proc_sig_ver_separation;
    table_proc[SIGS::SIG_CLOSE_PANEL]       = proc_sig_close_panel;
    table_proc[SIGS::SIG_REFRESH_CURSOR]    = proc_sig_refresh_cursor;
}

void EventHandler::regular_sig()
{
    int ret_sig;
    if ((ret_sig = proc_sig_send_error(user_data)) != SIGS::END_SIGS)
        q_sig.push(ret_sig);

    if ((ret_sig = proc_sig_send_resize(user_data)) != SIGS::END_SIGS)
    {
        q_sig.push(ret_sig);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
    }
}

void EventHandler::keyboard_sig()
{
    int key = getch();
    switch (key)
    {
    case 'q':
        q_sig.push(SIGS::SIG_EXIT);
        break;
    case 'w':
        q_sig.push(SIGS::SIG_CHANGE_WORKDIR_UP);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case 's':
        q_sig.push(SIGS::SIG_CHANGE_WORKDIR_DOWN);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;

    case KEY_UP:
        q_sig.push(SIGS::SIG_CURSOR_UP);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case KEY_DOWN:
        q_sig.push(SIGS::SIG_CURSOR_DOWN);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case KEY_LEFT:
        q_sig.push(SIGS::SIG_CURSOR_LEFT);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case KEY_RIGHT:
        q_sig.push(SIGS::SIG_CURSOR_RIGHT);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;

    case 'i':
        q_sig.push(SIGS::SIG_OFFSET_PANEL_UP);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case 'k':
        q_sig.push(SIGS::SIG_OFFSET_PANEL_DOWN);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    
    case '\t':
        q_sig.push(SIGS::SIG_CHANGE_PANEL);
        q_sig.push(SIGS::SIG_REFRESH_CURSOR);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;

    case 22:    // ctrl + v
        q_sig.push(SIGS::SIG_VER_SEPARATION);
        q_sig.push(SIGS::SIG_REFRESH_CURSOR);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case 8:    // ctrl + h
        q_sig.push(SIGS::SIG_HOR_SEPARATION);
        q_sig.push(SIGS::SIG_REFRESH_CURSOR);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;
    case 23:   // ctrl + w
        q_sig.push(SIGS::SIG_CLOSE_PANEL);
        q_sig.push(SIGS::SIG_REFRESH_SCREEN);
        break;

    default:
        break;
    }
}

void EventHandler::extract_sig()
{
    usleep(sleep_time);
    if (!q_sig.empty())
    {
        locker.lock();
        int ret_sig = table_proc[q_sig.front()](user_data);
        if (ret_sig == SIGS::END_SIGS)
            q_sig.pop();
        else 
        {
            int& cur_sig = q_sig.front();
            cur_sig = ret_sig;
        }
        locker.unlock();
    }
}
