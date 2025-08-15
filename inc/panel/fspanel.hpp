#ifndef _FSPANEL_
#define _FSPANEL_

#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>
#include <string.h>
#include <algorithm>
#include <fstream>
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

    FSPanel() { 
        class_name = "fspanel";
    }

    void load_default_unicode_icon()
    {
        load_icon("dir",        L'\ueaf7');
        load_icon(".c",         L'\U000f0671');
        load_icon(".cpp",       L'\U000F0672');
        load_icon(".h",         L'\U000f0829');
        load_icon(".hpp",       L'\U000f0829');
        load_icon(".json",      L'\ueb0f');
        load_icon(".pdf",       L'\uf1c1');
        load_icon(".jpeg",      L'\uf00f');
        load_icon(".img",       L'\uf00f');
        load_icon(".png",       L'\uf00f');
        load_icon(".conf",      L'\ue615');
        load_icon(".ini",       L'\ue615');
        load_icon(".db",        L'\ue64d');
        load_icon(".deb",       L'\uebc5');
        load_icon(".zip",       L'\ueaef');
        load_icon(".css",       L'\ue749');
        load_icon(".html",      L'\ue736');
    }
    wchar_t get_icon(std::string type)
    {
        auto _icon = table_icon.find(type);
        if (_icon != table_icon.end())
            return _icon->second;
        return 0;

    }
    void load_icon(std::string type, wchar_t icon) { table_icon[type] = icon; }
    std::string parse_file(std::string file)
    {
        auto i = file.rfind(".");
        if (i != std::string::npos)
            return file.substr(i, file.size());
        return "";
    }

    void init_color_pair()
    {
        color_pair_cursor = COLOR_PAIR_CURSOR;
        color_pair_text = COLOR_PAIR_TEXT;
        color_pair_frame = COLOR_PAIR_FRAME;
        color_pair_icon = COLOR_PAIR_ICON;
    }

    void set_workspace_path(std::string path);
    std::string get_workspace_path() { return workspace_path; }

    std::vector<dir>& get_tree_dir() { return lst_dir; }
    int get_cnt_dirs() { return lst_dir.size(); }
    void clear_tree_dir() { lst_dir.clear(); }
    void read_dirs(std::string path);

    short color_pair_cursor;
    short color_pair_text;
    short color_pair_frame;
    short color_pair_icon;

    void calc_max_offset_panel();
    short get_max_hor_offset() { return max_hor_offset; }
    short get_max_ver_offset() { return max_ver_offset; }
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
