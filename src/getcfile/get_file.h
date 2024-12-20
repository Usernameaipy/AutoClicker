#ifndef GTK
#define GTK
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#endif
#ifndef GET_FILE_H
#define GET_FILE_H
#include <stdbool.h>
#include <stdio.h>

#include "file_rplus.h"
bool get_file(size_t *, const char *, size_t);
bool check_file(FILE *);
void change_entry(GtkEntry *entry, gpointer user_data);
#endif