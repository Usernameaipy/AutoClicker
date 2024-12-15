#ifndef X11_LIBS
#define X11_LIBS
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#endif
#ifndef GTK
#define GTK
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif
#ifndef CLICER_H
#define CLICER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../input/input.h"
#include "file_rplus.h"
typedef struct {
  Window target_window;
  size_t time;
  size_t quantity;
} thread_param;
void click_imitation(GtkWidget *, gpointer);
bool check_file(FILE *);
unsigned int get_winid(gint);
bool get_string(FILE *, char *, size_t);
void get_configuration_click_file(size_t *, size_t *);
bool create_file_conf(void);
void *thread_click(gpointer);
void change_entry_setcl(GtkEntry*, gpointer);
#endif
