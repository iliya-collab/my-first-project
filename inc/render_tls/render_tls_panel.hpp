#ifndef _RENDER_TLS_PANEL_
#define _RENDER_TLS_PANEL_

#include "panel/fspanel.hpp"
#include "panel/vispanel.hpp"
#include "render.hpp"

#include "app_state.hpp"

//void calc_size_panel(AppState* ptr_app);

void render_panel(AppState* ptr_app, Panel pl);

void refresh_screen(AppState* ptr_app);

void sep_ver(AppState* ptr_app);

void sep_hor(AppState* ptr_app);

void recalc_bufs(AppState* ptr_app);

void updates_buf_panels(AppState* ptr_app);

void move_nbuf(AppState* ptr_app, Panel pl);

int get_active_index(AppState* ptr_app, int nbuf);

/*void render_dirs(yx pos, FSPanel fspanel);
void render_fspanel(FSPanel fspanel);

void render_file(yx pos);
void render_vispanel();*/

#endif
