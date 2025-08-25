#ifndef _PANEL_
#define _PANEL_

#include "render_tls/render.hpp"
#include <string>

#define COLOR_PAIR_ACT_PANEL        1
#define COLOR_PAIR_CURSOR           2
#define COLOR_PAIR_TEXT             3
#define COLOR_PAIR_FRAME            4
#define COLOR_PAIR_ICON             5
#define COLOR_PAIR_SETTINGS_MODE    6

#define FRAME_BASE      {L'│', L'│', L'─', L'─', L'╭', L'╮', L'╰', L'╯'}
#define FRAME_DOUBLE    {L'║', L'║', L'═', L'═', L'╔', L'╗', L'╚', L'╝'}
#define FRAME_V2        {L'│', L'│', L' ', L'─', L' ', L' ', L'╰', L'╯'}

#define FRAME FRAME_BASE

enum CLASS_PANEL {
    NON,
    FSPANEL,
    VISPANEL,

    END_CLASS
};

typedef struct {
    int code;
    std::string msg;
} Error;

class Panel {
public:


        /*Panel(const Panel& other) {
            this->id = other.id;
            this->pos_panel = other.pos_panel;
            this->class_name = other.class_name;
            this->nbuf = other.nbuf;
            this->err = other.err;
        }*/
       /*Panel& operator = (const Panel& pl) {
        this->id = pl.id;
        this->pos_panel = pl.pos_panel;
        this->class_name = pl.class_name;
        this->err = pl.err;
        return *this;
    }*/
   
   
   Panel();
   
    bool is_cursor(yx cur);
    posPanel get_panel();
    void set_panel(posPanel pos_panel);

    short get_id();
    static short get_count_panel();
    std::string& get_class_name();
    Error get_last_error();

    bool operator == (const Panel& pl) const;
    
    short nbuf = 0;

protected:

    static short id_panel;
    short id;
    std::string class_name;
    posPanel pos_panel;
    Error err;
};

#endif
