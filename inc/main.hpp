#ifndef _MAIN_
#define _MAIN_

#include <locale.h>
#include <unistd.h>

#include "sigs/event_handler.hpp"
#include "render_tls/render_tls_panel.hpp"
#include "logs.hpp"

extern EventHandler event;
extern AppState app;

void init(int argc, char* argv[]);

void main_loop();

#endif
