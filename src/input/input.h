#ifndef X11_LIBS
#define X11_LIBS
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#endif
#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xrender.h>
#endif
#ifndef GTK
#define GTK
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif
#ifndef INPUT_H
#define INPUT_H
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../getcfile/get_file.h"
typedef enum action_type { actions_mouse, actions_key } action_type;
typedef struct {
  action_type type;
  union {
    struct {
      int x;
      int y;
    } mouse;
    struct {
      KeyCode key;
    } keyboard;
  };
} user_click;
bool clicks_alloc(size_t);
bool clicks_free(void);
bool reclicks_alloc(size_t);
void cp_user_click(user_click *, user_click *);
bool click_add(user_click *);
void *input_click(void *);
void get_quan_click(size_t *);
bool create_file_conf_q(void);
size_t get_len_now(void);
void record_mouse_click(Display *, XEvent *);
void record_key_press(Display *, XEvent *);
void thread_input(void);
void get_user_clic(user_click *);
void arr_print(void);
#endif