#ifndef _SIGS_
#define _SIGS_

enum SIGNAL {

    EXIT,                   // Выход из программы
    ERROR,                  // Ошибка в программе

    CURSOR_UP,              // Переместить курсор вверх
    CURSOR_DOWN,            // Переместить курсор вниз
    CURSOR_LEFT,            // Переместить курсор влево
    CURSOR_RIGHT,           // Переместить курсор вправо
    REFRESH_CURSOR,         // Обновление информации о курсоре

    OFFSET_PANEL_UP,
    OFFSET_PANEL_DOWN,
    OFFSET_PANEL_LEFT,
    OFFSET_PANEL_RIGHT,

    CLOSE_PANEL,
    REFRESH_SCREEN,
    CHANGE_PANEL,
    RESIZE_WIN,
    VER_SEPARATION,
    HOR_SEPARATION,
    MOVE_BUFFER,

    SETTINGS_MODE,
    NORMAL_MODE,
    EDIT_ITEM_UP,
    EDIT_ITEM_DOWN,
    SAVE_SETTINGS,

    CHANGE_WORKDIR_UP,
    CHANGE_WORKDIR_DOWN,
    
    END
};

#endif
