#ifndef _VISUAL_PANEL_
#define _VISUAL_PANEL_

#include "panel.hpp"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define Kb  1024

class VISPanel : public Panel {
public:

    VISPanel() {
        class_name = "vispanel";
    }

    void calc_max_offset_panel();

    void set_size_swap(uint64_t size) { max_size_swap_file = size; }
    std::string get_file() { return file; }
    void set_file(std::string path) { file = path; }
    void create_swap_file();
    void output_swap_file();
    void input_swap_file(int start, int end);
    std::vector<std::string> get_buf_file() { return buf_file; }
    void clear_buf_file() { buf_file.clear(); }
    void free_buffer() { free(buffer); }
    void read_file(int seek);
    //void read_file();
    void remove_all_swap_files()
    {
        for (auto sfile : lst_swap_files)
            std::remove(sfile.c_str());
    }
    char* buffer;

private:

    void trim(std::string& str);

    uint64_t max_size_swap_file;
    std::string swap_file;
    std::string file;
    std::vector<std::string> buf_file;
    std::vector<std::string> lst_swap_files;
};

#endif
