#include "panel/panel.hpp"
#include "logs.hpp"

short Panel::id_panel = 0;

Panel::Panel() { 
    id = id_panel;
    id_panel++;
    class_name = "Non";
}

posPanel Panel::get_panel() { 
    return pos_panel; 
}

void Panel::set_panel(posPanel pos_panel) { 
    this->pos_panel = pos_panel; 
}

bool Panel::is_cursor(yx cur) {
    if ( cur.x >= pos_panel.spos.x && 
        cur.y >= pos_panel.spos.y &&
        cur.x <= pos_panel.spos.x+pos_panel.size.x-1 && 
        cur.y <= pos_panel.spos.y+pos_panel.size.y-1)
        return true;
    return false;
}

short Panel::get_id() { 
    return id; 
}

short Panel::get_count_panel() { 
    return id_panel; 
}

std::string& Panel::get_class_name() { 
    return class_name; 
}

Error Panel::get_last_error() { 
    return err; 
}

bool Panel::operator == (const Panel& pl) const { 
    return id == pl.id; 
}