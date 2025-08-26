#ifndef _SETTINGS_PANEL_
#define _SETTINGS_PANEL_

#include "panel/panel.hpp"

class SettingsPanel : public Panel {

private:

    typedef struct {
        int cur_buf;
        int max_buf;
        std::string class_buf;
        bool mode_hard_cursor;

    } _Settings;

    _Settings settings;

public:

    _Settings& get_setup() { return settings; }

};

#endif