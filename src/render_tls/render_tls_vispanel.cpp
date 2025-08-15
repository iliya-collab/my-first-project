#include "render_tls/render_tls_panel.hpp"

/*void render_file(yx pos)
{
    std::string str;
    for (int i = 0; i < vispanel.get_buf_file().size(); i++)
    {
        if (pos.y == vispanel.get_panel().size.y-1)
            break;
        str = vispanel.get_buf_file()[i];
        vispanel.write_str(back_buf, pos, STWS(str), COLOR_PAIR_TEXT);
        pos.y++;
    }
}

void render_vispanel()
{
    vispanel.clear_area(back_buf);
    //vispanel.frame(back_buf, {L'━',L'┃',L'┏',L'┓',L'┗',L'┛'});
    vispanel.frame(back_buf, FRAME);
    vispanel.clear_buf_file();
    vispanel.input_swap_file(vispanel.ver_offset, vispanel.ver_offset+vispanel.get_panel().size.y-1);
    render_file({vispanel.get_panel().spos.y+1, vispanel.get_panel().spos.x+1});
}*/
