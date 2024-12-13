/*необходимые заголовочные файлы*/ #include<X11 / Xlib.h> #include<                                                        \
    X11 / keysym.h> /* KEYCODE - код клавиши, которую необходимо эмулировать.        \
                       В данном случае - это пробел. Все возможные значения      \
                       можно найти в файле /usr/include/X11/keysymdef.h */                                 \
    #define KEYCODE                                                                                                        \
        XK_space /* Функция, которая создаёт структуру события клавиатуры,  \
                    заполняет её, а затем исполняет. */                                          \
    void                                                                                                                   \
    key_event(Display *display, Window *win, Window *win_root, int keycode,                                                \
              int is_press){                                                                                               \
        /*Создаём событие клавиатуры*/ XKeyEvent                                                                           \
            event; /*Заполняем структуру/* /* is_press != 0 - нажать клавишу                \
                      (KeyPress), is_press == 0 - отжать (KeyRelease) :) */                                          \
        event.type = is_press != 0 ? KeyPress : KeyRelease;                                                                \
        event.display = display; event.window = *win; event.root = *win_root;                                              \
        event.subwindow = None; event.time = CurrentTime; event.x = 1;                                                     \
        event.y = 1; event.x_root = 1; event.y_root = 1;                                                                   \
        event.same_screen = True;                                                                                          \
        event.keycode = XKeysymToKeycode(display, keycode); event.state = 0;                                               \
        /*выполняем событие*/ XSendEvent(display, *win, True, KeyPressMask,                                                \
                                         (XEvent *)&event);} int main(){                                                   \
        Display *display; Window win_root, win_focus;                                                                      \
        int revert; /* Пытаемся получить указатель на 0 дисплей. Если попытка \
                       неудачна, то завершаем работу программы.*/                        \
        if ((display = XOpenDisplay(0)) == NULL) return -1;                                                                \
        /* Получаем главное окно текущего дисплея. */ win_root =                                                           \
            XDefaultRootWindow(display); /* Заполняем структуру окна, которая                 \
                                            находится в фокусе ввода X11.*/                           \
        XGetInputFocus(display, &win_focus, &revert);                                                                      \
        /* Эмулируем нажатие клавиши */ key_event(display, &win_focus,                                                     \
                                                  &win_root, KEYCODE, 1);                                                  \
        /* Эмулируем "отпускание" клавиши */ key_event(display, &win_focus,                                                \
                                                       &win_root, KEYCODE, 0);                                             \
        /*Удачно завершаем программу*/ XCloseDisplay(display); return 0;}
