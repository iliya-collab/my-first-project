#include "render_tls/render_tls_panel.hpp"

/*void render_dirs(yx pos, FSPanel fspanel)
{
    for (int i = fspanel.ver_offset; i < fspanel.get_cnt_dirs(); i++)
    {
        auto I = fspanel.get_tree_dir()[i];
        if (pos.y == fspanel.get_panel().size.y-1)
            break;

        wchar_t icon = L' ';
        if (I.type == TDIR)
            icon = fspanel.get_icon("dir");
        else
        {
            icon = fspanel.get_icon(fspanel.parse_file(I.name));
            if (icon == 0)
                icon = L' ';
        }

        std::wstring wstr;
        wstr += icon;
        wstr += STWS(" "+I.name);
        short color_pair = (pos.y == app.cursor.y && app.active_panel == fspanel.get_id_panel()-1) ? fspanel.color_pair_cursor : fspanel.color_pair_text;
        //fspanel.write_str(back_buf, pos, wstr, color_pair);
        puts_str_frame(app.back_buf, pos, pos.x+fspanel.get_panel().size.x-1, wstr, color_pair);

        pos.y++;
    }
}

void render_fspanel(FSPanel fspanel)
{
    clear_area(app.back_buf, fspanel.get_panel(), fspanel.color_pair_frame);
    frame(app.back_buf, FRAME, fspanel.get_panel(), fspanel.color_pair_frame);
    posPanel pos = fspanel.get_panel();
    puts_str_frame(app.back_buf, {pos.spos.y+1, pos.spos.x+1}, pos.spos.x+pos.size.x, STWS(fspanel.get_workspace_path()), fspanel.color_pair_frame);
    if ((app.err = fspanel.get_last_error()).code != 0)
        return;
    render_dirs({fspanel.get_panel().spos.y+2, fspanel.get_panel().spos.x+1}, fspanel);
}*/
