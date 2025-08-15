#include "render_tls/render.hpp"

void clear_log()
{
    std::ofstream fout;
    fout.open(LOGFILE, std::ios::trunc);
    fout.close();
}
void save_log(std::string msg)
{
    std::ofstream fout;
    fout.open(LOGFILE, std::ios::app);
    fout << msg << std::endl;
    fout.close();
}

std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(str);
}
std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

void hor_line(WINDOW* win, yx spos, int width, line ln, short color_pair)
{
    cchar_t sch;
    cchar_t lch;
    cchar_t ech;
    setcchar(&sch, &ln.sch, A_NORMAL, color_pair, NULL);
    setcchar(&lch, &ln.lch, A_NORMAL, color_pair, NULL);
    setcchar(&ech, &ln.ech, A_NORMAL, color_pair, NULL);
    mvwadd_wch(win, spos.y, spos.x,  &sch);
    //mvwadd_wch(win, spos.y, spos.x+width-3,  &ech);
    mvwadd_wch(win, spos.y, width-2,  &ech);
    for (int x = spos.x+1; x < width-1; x++)
        mvwadd_wch(win, spos.y, x,  &lch);
}

void ver_line(WINDOW* win, yx spos, int height, line ln, short color_pair)
{
    cchar_t tch;
    cchar_t lch;
    cchar_t bch;
    setcchar(&tch, &ln.sch, A_NORMAL, color_pair, NULL);
    setcchar(&lch, &ln.lch, A_NORMAL, color_pair, NULL);
    setcchar(&bch, &ln.ech, A_NORMAL, color_pair, NULL);
    mvwadd_wch(win, spos.y, spos.x,  &tch);
    mvwadd_wch(win, height-2, spos.x,  &bch);
    for (int y = spos.y+1; y < height-1; y++)
        mvwadd_wch(win, y, spos.x,  &lch);
}

/*void rdr_string(WINDOW* win, yx spos, int offset, std::wstring str, int max_len, short color_pair)
{
    int limit_offset = 0;
    size_t sz_str = str.size();
    std::wstring new_str;
    if (offset < sz_str)
        new_str = str.substr(offset, max_len);
    else new_str = L"";
    wattron(win, COLOR_PAIR(color_pair));
    mvwprintw(win, spos.y, spos.x, "%ls", new_str.c_str());
    wattroff(win, A_NORMAL);
}*/

void puts_str(WINDOW* win, yx spos, std::wstring str, short color_pair)
{
    wattron(win, COLOR_PAIR(color_pair));
    mvwprintw(win, spos.y, spos.x, "%ls", str.c_str());
    wattroff(win, A_NORMAL);
}

void puts_str_frame(WINDOW* win,yx spos, int x_end, std::wstring str, short color_pair)
{
    cchar_t ch;
    for (int x = spos.x, i = 0; x < x_end && i < str.size(); x++, i++)
    {
        setcchar(&ch, &str[i], A_NORMAL, color_pair, NULL);
        mvwadd_wch(win, spos.y, x, &ch);
    }
}

void frame(WINDOW* win, win_border wb, posPanel pos_panel, short color_pair)
{
    cchar_t ls, rs, ts, bs, tl, tr, bl, br;

    setcchar(&ls, &wb.ls, A_NORMAL, color_pair, NULL);
    setcchar(&rs, &wb.rs, A_NORMAL, color_pair, NULL);
    setcchar(&ts, &wb.ts, A_NORMAL, color_pair, NULL);
    setcchar(&bs, &wb.bs, A_NORMAL, color_pair, NULL);
    setcchar(&tl, &wb.tl, A_NORMAL, color_pair, NULL);
    setcchar(&tr, &wb.tr, A_NORMAL, color_pair, NULL);
    setcchar(&bl, &wb.bl, A_NORMAL, color_pair, NULL);
    setcchar(&br, &wb.br, A_NORMAL, color_pair, NULL);

    mvwadd_wch(win, pos_panel.spos.y, pos_panel.spos.x, &tl);
    mvwadd_wch(win, pos_panel.spos.y, pos_panel.spos.x+pos_panel.size.x-1, &tr);
    mvwadd_wch(win, pos_panel.spos.y+pos_panel.size.y-1, pos_panel.spos.x, &bl);
    mvwadd_wch(win, pos_panel.spos.y+pos_panel.size.y-1, pos_panel.spos.x+pos_panel.size.x-1, &br);

    hor_line(win, {pos_panel.spos.y,pos_panel.spos.x+1}, pos_panel.spos.x+pos_panel.size.x, {wb.ts,wb.ts,wb.ts}, color_pair);
    hor_line(win, {pos_panel.spos.y+pos_panel.size.y-1,pos_panel.spos.x+1}, pos_panel.spos.x+pos_panel.size.x, {wb.bs,wb.bs,wb.bs}, color_pair);
    ver_line(win, {pos_panel.spos.y+1,pos_panel.spos.x}, pos_panel.spos.y+pos_panel.size.y, {wb.ls,wb.ls,wb.ls}, color_pair);
    ver_line(win, {pos_panel.spos.y+1,pos_panel.spos.x+pos_panel.size.x-1}, pos_panel.spos.y+pos_panel.size.y, {wb.rs,wb.rs,wb.rs}, color_pair);
}

void clear_area(WINDOW* win, posPanel pos_panel, short color_pair)
{
    wchar_t fill = L' ';
    cchar_t cf;
    setcchar(&cf, &fill, A_NORMAL, color_pair, NULL);
    for (int y = pos_panel.spos.y; y < pos_panel.spos.y+pos_panel.size.y; y++)
        for (int x = pos_panel.spos.x; x < pos_panel.spos.x+pos_panel.size.x; x++)
             mvwadd_wch(win, y, x, &cf);
}