#include "main.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	init_curses();

	init_pair(COLOR_PAIR_TEXT,      75, 0);
	init_pair(COLOR_PAIR_FRAME,     81, 0);
	init_pair(COLOR_PAIR_CURSOR,    190, 0);
	init_pair(COLOR_PAIR_ACT_PANEL, 31, 0);
	init_pair(COLOR_PAIR_ICON,      184, 0);

	init_prog(argc, argv);
    
    clear_log();

	ev_hndr.init(&app);
	ev_hndr.init_table_sigs();
	ev_hndr.set_sleep_time(1000);
	ev_hndr.start();
    usleep(5000);

    ev_hndr.send_sig(SIGS::SIG_REFRESH_SCREEN);

	while (!app.ex)
        ev_hndr.extract_sig();
	
	return 0;
}
