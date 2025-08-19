#include "sigs/event_handler.hpp"
#include "render_tls/render_tls_panel.hpp"

int proc_sig::exit(void* user_data) 
{ 
    AppState* ptr_app = (AppState*)user_data;

    ptr_app->ex = true; 
    delwin(ptr_app->back_buf);
	endwin();
    
    return SIGNAL::END;
}

int proc_sig::error(void* user_data) 
{
    AppState* ptr_app = (AppState*)user_data;
    int ret_sig = SIGNAL::END;
    while (!ptr_app->q_err.empty())
    {
        if (ptr_app->q_err.front().code < 0)
        {
            save_log("Error : " + ptr_app->q_err.front().msg);
            ret_sig = SIGNAL::EXIT;
        }
        if (ptr_app->q_err.front().code > 0)
        {
            save_log("Warning : " + ptr_app->q_err.front().msg);
            ret_sig = SIGNAL::END;
        }
        ptr_app->q_err.pop();
    }
    return ret_sig;
}

int proc_sig::send_error(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (!ptr_app->q_err.empty())
        return SIGNAL::ERROR;
    return SIGNAL::END;
}

int proc_sig::send_resize(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    int new_screen_height = 0;
    int new_screen_width = 0;
    getmaxyx(stdscr, new_screen_height, new_screen_width);
    if (ptr_app->screen_height != new_screen_height || ptr_app->screen_width != new_screen_width)
    {
        ptr_app->screen_height = new_screen_height;
        ptr_app->screen_width = new_screen_width;
        return SIGNAL::RESIZE_WIN;
    }
    return SIGNAL::END;
}

int proc_sig::cursor_up(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (ptr_app->cursor.y > ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.y+1)
        ptr_app->cursor.y--;
    return SIGNAL::END;
}

int proc_sig::cursor_down(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (ptr_app->cursor.y < ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.y + ptr_app->buf_panels[ptr_app->active_panel].get_panel().size.y-2)
        ptr_app->cursor.y++;
    return SIGNAL::END;
}

int proc_sig::cursor_left(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (ptr_app->cursor.x > ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.x+1)
        ptr_app->cursor.x--;
    return SIGNAL::END;
}

int proc_sig::cursor_right(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (ptr_app->cursor.x < ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.x + ptr_app->buf_panels[ptr_app->active_panel].get_panel().size.x-1)
        ptr_app->cursor.x++;
    return SIGNAL::END;
}

/*void proc_offset_panel_up()
{
    if (pp.active_panel == IDPANEL::LFSPANEL && lfspanel.ver_offset > 0)
        lfspanel.ver_offset--;
    if (pp.active_panel == IDPANEL::RFSPANEL && rfspanel.ver_offset > 0)
        rfspanel.ver_offset--;
}

void proc_offset_panel_down()
{
    if (pp.active_panel == IDPANEL::LFSPANEL && lfspanel.ver_offset < lfspanel.get_max_ver_offset())
        lfspanel.ver_offset++;
    if (pp.active_panel == IDPANEL::RFSPANEL && rfspanel.ver_offset < rfspanel.get_max_ver_offset())
        rfspanel.ver_offset++;
}

void proc_offset_panel_left()
{
    if (pp.active_panel == IDPANEL::LFSPANEL && lfspanel.hor_offset > 0)
        lfspanel.hor_offset--;
    if (pp.active_panel == IDPANEL::RFSPANEL && rfspanel.hor_offset > 0)
        rfspanel.hor_offset--;
}

void proc_offset_panel_right()
{
    if (pp.active_panel == IDPANEL::LFSPANEL && lfspanel.hor_offset < lfspanel.get_max_hor_offset())
        lfspanel.hor_offset++;
    if (pp.active_panel == IDPANEL::RFSPANEL && rfspanel.hor_offset < rfspanel.get_max_hor_offset())
        rfspanel.hor_offset++;
}*/

/*void proc_change_workdir_down()
{
    if (pp.active_panel == IDPANEL::LFSPANEL)
    {
        std::string cur_wp = lfspanel.get_workspace_path();
        auto i = cur_wp.rfind('/');
        std::string new_wp = cur_wp.substr(0, i);
        if (new_wp == "")
            new_wp = "/";
        lfspanel.set_workspace_path(new_wp);
        lfspanel.hor_offset = 0;
        lfspanel.ver_offset = 0;
        lfspanel.clear_tree_dir();
        lfspanel.read_dirs(lfspanel.get_workspace_path());
    }
    if (pp.active_panel == IDPANEL::RFSPANEL)
    {
        std::string cur_wp = rfspanel.get_workspace_path();
        auto i = cur_wp.rfind('/');
        std::string new_wp = cur_wp.substr(0, i);
        if (new_wp == "")
            new_wp = "/";
        rfspanel.set_workspace_path(new_wp);
        rfspanel.hor_offset = 0;
        rfspanel.ver_offset = 0;
        rfspanel.clear_tree_dir();
        rfspanel.read_dirs(rfspanel.get_workspace_path());
    }
}

void proc_change_workdir_up()
{
    if (pp.active_panel == IDPANEL::LFSPANEL)
    {
        int i = lfspanel.ver_offset+cursor.y-2;
        if (i >= 0 && i < lfspanel.get_cnt_dirs())
        {
            if (lfspanel.get_tree_dir()[i].type == TDIR)
            {
                std::string new_wp = lfspanel.get_tree_dir()[i].fullpath;
                lfspanel.set_workspace_path(new_wp);
                lfspanel.hor_offset = 0;
                lfspanel.ver_offset = 0;
                lfspanel.clear_tree_dir();
                lfspanel.read_dirs(lfspanel.get_workspace_path());
            }
        }
    }
    if (pp.active_panel == IDPANEL::RFSPANEL)
    {
        int i = rfspanel.ver_offset+cursor.y-2;
        if (i >= 0 && i < rfspanel.get_cnt_dirs())
            if (rfspanel.get_tree_dir()[i].type == TDIR)
            {
                std::string new_wp = rfspanel.get_tree_dir()[i].fullpath;
                rfspanel.set_workspace_path(new_wp);
                rfspanel.hor_offset = 0;
                rfspanel.ver_offset = 0;
                rfspanel.clear_tree_dir();
                rfspanel.read_dirs(rfspanel.get_workspace_path());
            }
    }
}*/

int proc_sig::refresh_screen(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    refresh_screen(ptr_app);
    return SIGNAL::END;
}

int proc_sig::resize_win(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    clear();
    endwin();
    refresh();
    resizeterm(ptr_app->screen_height, ptr_app->screen_width);
    clear_area(ptr_app->back_buf, {{0,0}, {ptr_app->screen_height-1, ptr_app->screen_width-1}}, COLOR_PAIR_FRAME);
    return SIGNAL::END;
}

int proc_sig::change_panel(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    if (ptr_app->active_buf < ptr_app->count_panels-1)
        ptr_app->active_buf++;
    else ptr_app->active_buf = 0;
    ptr_app->active_panel = get_active_index(ptr_app, ptr_app->active_buf);
    ptr_app->cursor = { ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.y+1, ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.x+1 };
    return SIGNAL::END;
}

int proc_sig::refresh_cursor(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    move(ptr_app->cursor.y, ptr_app->cursor.x);
    return SIGNAL::END;
}

int proc_sig::hor_separation(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    sep_hor(ptr_app);
    updates_buf_panels(ptr_app);
    recalc_bufs(ptr_app);
    return SIGNAL::END;
}

int proc_sig::ver_separation(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    sep_ver(ptr_app);
    updates_buf_panels(ptr_app);
    recalc_bufs(ptr_app);
    return SIGNAL::END;
}

int proc_sig::close_panel(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    auto parent = ptr_app->tree_panels.find_parent(ptr_app->buf_panels[ptr_app->active_panel]);
    ptr_app->tree_panels.remove_childs(parent);
    updates_buf_panels(ptr_app);
    recalc_bufs(ptr_app);
    return SIGNAL::END;
}

int proc_sig::move_buffer(void* user_data)
{
    AppState* ptr_app = (AppState*)user_data;
    auto pl = ptr_app->buf_panels[ptr_app->active_panel];
    move_nbuf(ptr_app, pl);
    ptr_app->active_panel = get_active_index(ptr_app, ptr_app->active_buf);
    ptr_app->cursor = { ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.y+1, ptr_app->buf_panels[ptr_app->active_panel].get_panel().spos.x+1 };
    return SIGNAL::END;
}