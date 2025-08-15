#ifndef _MAIN_
#define _MAIN_

#include <locale.h>
#include <math.h>

#include "sigs/event_handler.hpp"
#include "render_tls/render_tls_panel.hpp"

EventHandler ev_hndr;

AppState app = {};

int init_curses()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    timeout(-1);
    start_color();
    
    if (!has_colors())
        app.q_err.push({ .code = 1, .msg = "Your terminal does not support color display" });
    if (can_change_color() == false)
        app.q_err.push({ .code = 1, .msg = "Your terminal does not support changing colors" });

    getmaxyx(stdscr, app.screen_height, app.screen_width);
    app.back_buf = newwin(0, 0, 0, 0);
	if (app.back_buf == NULL)
        app.q_err.push({ .code = -1, .msg = "Incorrect initialization of the screen buffer" });
    
    return 0;
}

void init_prog(int argc, char* argv[])
{
    clear();
    printw("Program Initialization\n");
    printw("----------------------------------------------------------\n");

    if (argc < 2)
        app.q_err.push({ .code = -1, .msg = "To run the program, you need to pass the parameters" });
    app.active_panel = 0;

    Panel root_panel;
    root_panel.set_panel( {{0,0}, {app.screen_height, app.screen_width}} );
    app.cursor = { root_panel.get_panel().spos.y+1, root_panel.get_panel().spos.x+1 };

    app.tree_panels.set_root(root_panel);
    app.count_panels = app.tree_panels.get_count();
    app.tree_panels.get_root()->pl.nbuf = 0;
    app.tree_panels.get_child(app.buf_panels);
    
    //calc_size_panel(&app);
    printw("Screen size     : %d:%d\n", app.screen_height, app.screen_width);
    printw("Cursor          : %d:%d\n", app.cursor.y, app.cursor.x);
    printw("Count panels    : %d\n", app.count_panels);
    printw("Active panel    : %d\n", app.active_panel);
    printw("----------------------------------------------------------\n\n");
    
    /*printw("All Panels\n");
    for (auto next_panel = app.buf_panels.begin(); next_panel != app.buf_panels.end(); next_panel++)
    printw("ID panel : %d   Class name : %s   Position : %d:%d %d:%d\n", 
        (*next_panel).get_id(),
        (*next_panel).get_class_name().c_str(),
        (*next_panel).get_panel().spos.y, (*next_panel).get_panel().spos.x, 
        (*next_panel).get_panel().spos.y+(*next_panel).get_panel().size.y, 
        (*next_panel).get_panel().spos.x+(*next_panel).get_panel().size.x
    );
    printw("----------------------------------------------------------\n\n");*/
    
    printw("Press any key or [q] to exit...");
    refresh();
    if (getch() == 'q') 
        ev_hndr.send_sig(SIGS::SIG_EXIT);
    clear();
    move(app.cursor.y, app.cursor.x);
}


#endif
