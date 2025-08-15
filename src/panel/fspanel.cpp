#include "panel/fspanel.hpp"

void FSPanel::calc_max_offset_panel()
{
    int voffset = lst_dir.size()-pos_panel.size.y+3;
    int hoffset = workspace_path.size()-pos_panel.size.x+2;
    max_hor_offset = fmax(max_hor_offset, hoffset);
    max_ver_offset = voffset;
    int j = 0;
    for (int i = ver_offset; i < lst_dir.size(); i++)
    {
        if (j == pos_panel.size.y-1)
            break;
        auto I = lst_dir[i];
        hoffset = I.name.size()-pos_panel.size.x+2;
        max_hor_offset = fmax(max_hor_offset, hoffset);
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
