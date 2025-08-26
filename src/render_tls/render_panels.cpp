#include "app_state.hpp"
#include <algorithm>
#include <sstream>

static bool sort_nbuf(Panel pl1, Panel pl2) { return pl1.nbuf < pl2.nbuf; }

void recalc_bufs(AppState* ptr_app)
{
    short nbuf = 0;
    for (auto i = ptr_app->buf_panels.begin(); i != ptr_app->buf_panels.end(); ++i, nbuf++)
        (*i).nbuf = nbuf;
}

void updates_buf_panels(AppState* ptr_app) {
    ptr_app->buf_panels.clear();
    ptr_app->tree_panels.get_childs(ptr_app->buf_panels);
    ptr_app->count_panels = ptr_app->buf_panels.size();
}

void sep_ver(AppState* ptr_app)
{
    Panel sep_panel = ptr_app->buf_panels[ptr_app->active_panel];
    Panel left_panel;
    Panel right_panel;
    short y = sep_panel.get_panel().spos.y;
    short x = sep_panel.get_panel().spos.x;
    short szY = sep_panel.get_panel().size.y;
    short szX = sep_panel.get_panel().size.x/2;
    left_panel.set_panel({ {y,x}, {szY, szX} });
    right_panel.set_panel({ {y,x+szX}, {szY, szX+sep_panel.get_panel().size.x%2} });
    ptr_app->tree_panels.push_child(sep_panel, left_panel, right_panel);
}

void sep_hor(AppState* ptr_app)
{
    Panel sep_panel = ptr_app->buf_panels[ptr_app->active_panel];
    Panel top_panel;
    Panel bottom_panel;
    short y = sep_panel.get_panel().spos.y;
    short x = sep_panel.get_panel().spos.x;
    short szY = sep_panel.get_panel().size.y/2;
    short szX = sep_panel.get_panel().size.x;
    top_panel.set_panel({ {y,x}, {szY, szX} });
    bottom_panel.set_panel({ {y+szY,x}, {szY+sep_panel.get_panel().size.y%2, szX} });
    ptr_app->tree_panels.push_child(sep_panel, top_panel, bottom_panel);
}

/*void calc_size_panel(AppState* ptr_app)
{
    int next_spos_y = 0;
    int next_spos_x = 0;
    int next_height = ptr_app->screen_height;
    int next_width = ptr_app->screen_width/ptr_app->count_panels;
    for (int next_panel = 0; next_panel < ptr_app->buf_panels.size(); next_panel++)
    {
        ptr_app->buf_panels[next_panel].set_panel({{next_spos_y, next_spos_x}, {next_height, next_width}});
        next_spos_x += next_width;
    }
    auto end_pos_panel = ptr_app->buf_panels[ptr_app->count_panels-1].get_panel();
    int d = ptr_app->screen_width - end_pos_panel.spos.x;
    end_pos_panel = {
        {end_pos_panel.spos.y, end_pos_panel.spos.x},
        {end_pos_panel.size.y, end_pos_panel.size.x+ptr_app->screen_width%next_width}
    };
    ptr_app->buf_panels[ptr_app->count_panels-1].set_panel(end_pos_panel);
}*/

void render_panel(AppState* ptr_app, Panel pl)
{
    short color = (pl.nbuf == ptr_app->active_buf) ? COLOR_PAIR_ACT_PANEL : COLOR_PAIR_FRAME;
    clear_area(ptr_app->back_buf, pl.get_panel(), color);
    frame(ptr_app->back_buf, FRAME, pl.get_panel(), color);
    std::string title = "<"+std::to_string(pl.nbuf)+">"+pl.get_class_name();
    puts_str(ptr_app->back_buf, {pl.get_panel().spos.y, pl.get_panel().spos.x+2}, s2ws(title), color);
}

static void handle_normal_mode(AppState* ptr_app) {
    for (auto next_panel = ptr_app->buf_panels.begin(); next_panel != ptr_app->buf_panels.end(); ++next_panel) {
        render_panel(ptr_app, (*next_panel));
    }
}

static void handle_settings_mode(AppState* ptr_app) {
    clear_area(ptr_app->back_buf, ptr_app->settings.get_panel(), COLOR_PAIR_SETTINGS_MODE);
    frame(ptr_app->back_buf, FRAME, ptr_app->settings.get_panel(), COLOR_PAIR_SETTINGS_MODE);
    std::wstring title = L"  Settings  ";
    puts_str(ptr_app->back_buf, {0, ptr_app->settings.get_panel().size.x/2-(int)title.size()}, title, COLOR_PAIR_SETTINGS_MODE);

    std::wstringstream ss;
    std::wstring wstr;
    int y = 1;
    auto cur_settings = ptr_app->settings.get_setup();

    puts_str(ptr_app->back_buf, {++y, 2}, L"Buffer : " + std::to_wstring(cur_settings.cur_buf), COLOR_PAIR_FRAME);
    puts_str(ptr_app->back_buf, {++y, 2}, L"Class : " + s2ws(cur_settings.class_buf), COLOR_PAIR_FRAME);
    puts_str(ptr_app->back_buf, {++y, 2}, std::wstring(L"Mode hard cursor : ") + ((cur_settings.mode_hard_cursor) ? L"true" : L"false"), COLOR_PAIR_FRAME);
}

void refresh_screen(AppState* ptr_app)
{
    switch (ptr_app->mode)
    {
    case MODE::NORMAL:
        handle_normal_mode(ptr_app);
        break;
    
    case MODE::SETTINGS:
        handle_settings_mode(ptr_app);
        break;

    default:
        break;
    }
   
    copywin(ptr_app->back_buf, stdscr, 0, 0, 0, 0, ptr_app->screen_height - 1, ptr_app->screen_width - 1, 0);
    refresh();
}

static void swap_nbuf(Panel& pl1, Panel& pl2) 
{
    int n = pl1.nbuf;
    pl1.nbuf = pl2.nbuf;
    pl2.nbuf = n;
}

int get_active_index(AppState* ptr_app, int nbuf)
{
    for (int i = 0; i < ptr_app->buf_panels.size(); i++)
        if (ptr_app->buf_panels[i].nbuf == nbuf)
            return i;
    return -1;
}

void move_nbuf(AppState* ptr_app, Panel pl)
{
    if (ptr_app->active_panel == ptr_app->count_panels-1)
        swap_nbuf(ptr_app->buf_panels[0], ptr_app->buf_panels[ptr_app->active_panel]);
    else 
        swap_nbuf(ptr_app->buf_panels[ptr_app->active_panel], ptr_app->buf_panels[ptr_app->active_panel + 1]);
}
