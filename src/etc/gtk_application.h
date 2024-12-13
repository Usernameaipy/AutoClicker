#ifndef GTK
#define GTK
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif
#ifndef GTK_APP_H
#define GTK_APP_H
#include "../clicer/clicer.h"
#include "../clicer/get_id_name_win.h"
void an_activate(GtkApplication *);
void create_combo_box(GtkWidget *);
void callback_for_combo_name(GtkComboBox *, gpointer);
#endif