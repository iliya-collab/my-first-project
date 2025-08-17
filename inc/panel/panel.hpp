#ifndef _PANEL_
#define _PANEL_
#include "render_tls/render.hpp"
#include "logs.hpp"
#include <string>
#include <vector>

#define COLOR_PAIR_FRAME        1
#define COLOR_PAIR_CURSOR       2
#define COLOR_PAIR_TEXT         3
#define COLOR_PAIR_ACT_PANEL    4
#define COLOR_PAIR_ICON         5

#define FRAME_BASE      {L'│', L'│', L'─', L'─', L'╭', L'╮', L'╰', L'╯'}
#define FRAME_DOUBLE    {L'║', L'║', L'═', L'═', L'╔', L'╗', L'╚', L'╝'}
#define FRAME_V2        {L'│', L'│', L' ', L'─', L' ', L' ', L'╰', L'╯'}

#define FRAME FRAME_BASE

enum IDPANEL {
    LFSPANEL,
    RFSPANEL
};

typedef struct {
    int code;
    std::string msg;
} Error;

class Panel {
public:

    Panel() { 
        id = id_panel;
        id_panel++;
    }

    /*Panel(const Panel& other) {
        this->id = other.id;
        this->pos_panel = other.pos_panel;
        this->class_name = other.class_name;
        this->nbuf = other.nbuf;
        this->err = other.err;
    }*/

    posPanel get_panel() { return pos_panel; }
    void set_panel(posPanel pos_panel) { this->pos_panel = pos_panel; }

    /*bool is_cursor(yx cur) {
        if (cur.x >= pos_panel.spos.x && cur.y >= pos_panel.spos.y &&
            cur.x <= pos_panel.spos.x+pos_panel.size.x-1 && cur.y <= pos_panel.spos.y+pos_panel.size.y-1)
            return true;
        return false;
    }*/

    short get_id() { return id; }
    static short get_count_panel() { return id_panel; }
    std::string get_class_name() { return class_name; }
    Error get_last_error() { return err; }

    bool operator == (const Panel& pl) const { return id == pl.id; }
    
    /*Panel& operator = (const Panel& pl) {
        this->id = pl.id;
        this->pos_panel = pl.pos_panel;
        this->class_name = pl.class_name;
        this->err = pl.err;
        return *this;
    }*/
    
    short nbuf = 0;

protected:

    static short id_panel;
    short id;
    std::string class_name;
    posPanel pos_panel;
    Error err;
};

#endif
