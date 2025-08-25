#ifndef _FSPANEL_
#define _FSPANEL_

#include <vector>
#include <map>

#include "panel.hpp"

#define TDIR   1
#define TFILE  2

typedef struct {
    std::string fullpath;
    std::string name;
    short type;
} dir;

class FSPanel : public Panel {
public:

    FSPanel();

    void load_default_unicode_icon();
    wchar_t get_icon(std::string type);
    void load_icon(std::string type, wchar_t icon);
    std::string parse_file(std::string file);

    void init_color_pair();

    std::string get_workspace_path();
    std::vector<dir>& get_tree_dir();
    int get_cnt_dirs();
    void clear_tree_dir();
    short get_max_hor_offset();
    short get_max_ver_offset();

    void set_workspace_path(std::string path);
    void read_dirs(std::string path);

    short color_pair_cursor;
    short color_pair_text;
    short color_pair_frame;
    short color_pair_icon;

    void calc_max_offset_panel();
    short hor_offset;
    short ver_offset;

private:

    short max_hor_offset;
    short max_ver_offset;

    std::string workspace_path;

    std::map<std::string, wchar_t> table_icon;
    std::vector<dir> lst_dir;
};

#endif
