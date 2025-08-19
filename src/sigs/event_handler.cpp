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
    table_proc = (_proc_sig_*)malloc(SIGNAL::END * sizeof(_proc_sig_));
    table_proc[SIGNAL::EXIT]                = proc_sig::exit;
    table_proc[SIGNAL::ERROR]               = proc_sig::error;
    table_proc[SIGNAL::CURSOR_UP]           = proc_sig::cursor_up;
    table_proc[SIGNAL::CURSOR_DOWN]         = proc_sig::cursor_down;
    table_proc[SIGNAL::CURSOR_LEFT]         = proc_sig::cursor_left;
    table_proc[SIGNAL::CURSOR_RIGHT]        = proc_sig::cursor_right;
    table_proc[SIGNAL::REFRESH_SCREEN]      = proc_sig::refresh_screen;
    table_proc[SIGNAL::RESIZE_WIN]          = proc_sig::resize_win;
    table_proc[SIGNAL::CHANGE_PANEL]        = proc_sig::change_panel;
    table_proc[SIGNAL::HOR_SEPARATION]      = proc_sig::hor_separation;
    table_proc[SIGNAL::VER_SEPARATION]      = proc_sig::ver_separation;
    table_proc[SIGNAL::CLOSE_PANEL]         = proc_sig::close_panel;
    table_proc[SIGNAL::REFRESH_CURSOR]      = proc_sig::refresh_cursor;
    table_proc[SIGNAL::MOVE_BUFFER]         = proc_sig::move_buffer;
}

void EventHandler::regular_sig()
{
    int ret_sig;
    if ((ret_sig = proc_sig::send_error(user_data)) != SIGNAL::END)
        q_sig.push(ret_sig);

    if ((ret_sig = proc_sig::send_resize(user_data)) != SIGNAL::END)
    {
        q_sig.push(ret_sig);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
    }
}

void EventHandler::keyboard_sig()
{
    int key = getch();
    switch (key)
    {
    case 'q':
        q_sig.push(SIGNAL::EXIT);
        break;
    case 'w':
        q_sig.push(SIGNAL::CHANGE_WORKDIR_UP);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case 's':
        q_sig.push(SIGNAL::CHANGE_WORKDIR_DOWN);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;

    case KEY_UP:
        q_sig.push(SIGNAL::CURSOR_UP);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case KEY_DOWN:
        q_sig.push(SIGNAL::CURSOR_DOWN);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case KEY_LEFT:
        q_sig.push(SIGNAL::CURSOR_LEFT);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case KEY_RIGHT:
        q_sig.push(SIGNAL::CURSOR_RIGHT);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;

    case 'i':
        q_sig.push(SIGNAL::OFFSET_PANEL_UP);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case 'k':
        q_sig.push(SIGNAL::OFFSET_PANEL_DOWN);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    
    case '\t':
        q_sig.push(SIGNAL::CHANGE_PANEL);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;

    case 22:    // ctrl + v
        q_sig.push(SIGNAL::VER_SEPARATION);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case 8:    // ctrl + h
        q_sig.push(SIGNAL::HOR_SEPARATION);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case 23:   // ctrl + w
        q_sig.push(SIGNAL::CLOSE_PANEL);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
        break;
    case KEY_BTAB:  // shift + tab
        q_sig.push(SIGNAL::MOVE_BUFFER);
        q_sig.push(SIGNAL::REFRESH_CURSOR);
        q_sig.push(SIGNAL::REFRESH_SCREEN);
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
        if (ret_sig == SIGNAL::END)
            q_sig.pop();
        else 
        {
            int& cur_sig = q_sig.front();
            cur_sig = ret_sig;
        }
        locker.unlock();
    }
}
