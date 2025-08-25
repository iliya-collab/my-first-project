#include "panel/fspanel.hpp"

#include <string.h>
#include <algorithm>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>

FSPanel::FSPanel() { 
    class_name = "fspanel";
}

void FSPanel::load_default_unicode_icon() {
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

wchar_t FSPanel::get_icon(std::string type) {
    auto _icon = table_icon.find(type);
    if (_icon != table_icon.end())
        return _icon->second;
    return 0;

}

void FSPanel::load_icon(std::string type, wchar_t icon) { 
    table_icon[type] = icon; 
}

std::string FSPanel::parse_file(std::string file) {
    auto i = file.rfind(".");
    if (i != std::string::npos)
        return file.substr(i, file.size());
    return "";
}

void FSPanel::init_color_pair() {
    color_pair_cursor = COLOR_PAIR_CURSOR;
    color_pair_text = COLOR_PAIR_TEXT;
    color_pair_frame = COLOR_PAIR_FRAME;
    color_pair_icon = COLOR_PAIR_ICON;
}

std::string FSPanel::get_workspace_path() { 
    return workspace_path; 
}

std::vector<dir>& FSPanel::get_tree_dir() { 
    return lst_dir; 
}

int FSPanel::get_cnt_dirs() { 
    return lst_dir.size(); 
}

void FSPanel::clear_tree_dir() { 
    lst_dir.clear(); 
}

short FSPanel::get_max_hor_offset() { 
    return max_hor_offset; 
}

short FSPanel::get_max_ver_offset() {
    return max_ver_offset; 
}


void FSPanel::calc_max_offset_panel()
{
    int voffset = lst_dir.size()-pos_panel.size.y+3;
    int hoffset = workspace_path.size()-pos_panel.size.x+2;
    max_hor_offset = max_hor_offset > hoffset ? max_hor_offset : hoffset;
    max_ver_offset = voffset;
    int j = 0;
    for (int i = ver_offset; i < lst_dir.size(); i++)
    {
        if (j == pos_panel.size.y-1)
            break;
        auto I = lst_dir[i];
        hoffset = I.name.size()-pos_panel.size.x+2;
        max_hor_offset = max_hor_offset > hoffset ? max_hor_offset : hoffset;
        j++;
    }
}

void FSPanel::set_workspace_path(std::string path)
{
    if (path == ".")
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            workspace_path = cwd;
    }
    else
        workspace_path = path;
}


void FSPanel::read_dirs(std::string path)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path.c_str()))) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        std::string name = entry->d_name;
        std::string full_path;
        if (path == "/")
            full_path = "/"+name;
        else
            full_path = path+"/"+name;

        struct stat statbuf;
        if (stat(full_path.c_str(), &statbuf) == -1)
        {
            perror("stat");
            continue;
        }

        short type = (S_ISDIR(statbuf.st_mode)) ? TDIR : TFILE;
        lst_dir.push_back({full_path, name, type});
    }

    closedir(dir);
}
