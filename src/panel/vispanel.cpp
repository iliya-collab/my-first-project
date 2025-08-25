#include "panel/vispanel.hpp"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*void VISPanel::calc_max_offset_panel()
{
    int voffset = buf_file.size()-pi.size.y+3;
    max_ver_offset = fmax(max_ver_offset, voffset);

    int hoffset = 0;
    int j = 0;
    for (int i = 0; i < buf_file.size(); i++)
    {
        if (j == pi.size.y-1)
            break;
        hoffset = buf_file[i].size()-pi.size.x+2;
        max_hor_offset = fmax(max_hor_offset, hoffset);
        j++;
    }
}

void VISPanel::create_swap_file()
{
    auto i = file.rfind("/");
    swap_file = file.substr(i+1, file.size()) + ".swap";
    std::ofstream fout;
    fout.open(swap_file);
    fout.close();
    lst_swap_files.push_back(swap_file);
}

void VISPanel::output_swap_file()
{
    int fd = open(swap_file.c_str(), O_WRONLY);
    if (fd == -1)
    {
        err.code = -1;
        err.msg_err = "Can not open file";
        return;
    }
    if (write(fd, buffer, max_size_swap_file) == -1)
    {
        err.code = -1;
        err.msg_err = "Can not write file";
        return;
    }
    close(fd);
}

void VISPanel::input_swap_file(int start, int end)
{
    std::ifstream fin;
    fin.open(swap_file);
    if (!fin.is_open())
        return;
    std::string buf;
    int i = 0;
    while (std::getline(fin, buf))
    {
        if (i == end)
            break;
        if (i >= start)
        {
            trim(buf);
            buf_file.push_back(buf);
        }
        i++;
    }
    fin.close();
}

void VISPanel::trim(std::string& str)
{
    auto it = str.find("\t");
    while (it != std::string::npos)
    {
        str.replace(it, 1, "  ");
        it = str.find("\t");
    }

}


void VISPanel::read_file(int seek)
{
    buffer = (char*)malloc(max_size_swap_file+1);
    if (buffer == NULL)
    {
        err.code = -1;
        err.msg_err = "Failed to allocate memory for the file buffer";
        return;
    }
    memset(buffer, 0, max_size_swap_file+1);
    int fd = open(file.c_str(), O_RDONLY);
    if (fd == -1)
    {
        err.code = -1;
        err.msg_err = "Can not open file";
        return;
    }
    if (lseek(fd, seek, SEEK_SET) == -1)
    {
        err.code = -1;
        err.msg_err = "Can not offset file";
        return;
    }
    if (read(fd, buffer, max_size_swap_file) == -1)
    {
        err.code = -1;
        err.msg_err = "Can not read file";
        return;
    }
    close(fd);
}*/

