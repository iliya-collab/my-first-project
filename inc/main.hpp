#ifndef _MAIN_
#define _MAIN_

#include <locale.h>
#include <math.h>

#include "sigs/event_handler.hpp"
#include "render_tls/render_tls_panel.hpp"

EventHandler event;

AppState app = {};

int init_curses() {
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

void init_theme() {
    init_pair(COLOR_PAIR_TEXT,          75, 0);
	init_pair(COLOR_PAIR_ACT_PANEL,     81, 0);
	init_pair(COLOR_PAIR_CURSOR,        190, 0);
	init_pair(COLOR_PAIR_FRAME,         31, 0);
	init_pair(COLOR_PAIR_ICON,          184, 0);
}

void init_prog(int argc, char* argv[]) {
    if (argc < 2)
        app.q_err.push({ .code = -1, .msg = "To run the program, you need to pass the parameters" });
    app.active_panel = 0;
    
    Panel root_panel;
    root_panel.set_panel( {{0,0}, {app.screen_height, app.screen_width}} );
    app.cursor = { root_panel.get_panel().spos.y+1, root_panel.get_panel().spos.x+1 };
    
    app.tree_panels.set_root(root_panel);
    app.count_panels = app.tree_panels.get_count();
    app.tree_panels.get_root()->pl.nbuf = 0;
    app.tree_panels.get_childs(app.buf_panels);
    move(app.cursor.y, app.cursor.x);
    
    clear_log();
    save_log("Program Initialization");
    save_log("----------------------------------------------------------");
    save_log("Screen size     : " + std::to_string(app.screen_height) + ":" + std::to_string(app.screen_width));
    save_log("----------------------------------------------------------");
}

void init(int argc, char* argv[]) {
    init_curses();
    init_theme();
    init_prog(argc, argv);
}

void main_loop() {
    event.init(&app);
	event.init_table_sigs();
	event.set_sleep_time(1000);
	event.start();
    usleep(5000);

    event.send_sig(SIGNAL::REFRESH_SCREEN);

	while (!app.ex)
        event.extract_sig();
}

#endif
