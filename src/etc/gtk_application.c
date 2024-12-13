#include "gtk_application.h"

void an_activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  GtkWidget *button_start = gtk_button_new_with_label("Start");
  GtkWidget *button_remember = gtk_button_new_with_label("Remem");
  GtkWidget *text_area = gtk_text_view_new();
  GtkWidget *combo_box = gtk_combo_box_text_new();
  GtkWidget *widget_cord = gtk_fixed_new();
  gtk_window_set_default_size(GTK_WINDOW(window), 665, 330);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_area));

  create_combo_box(combo_box);

  gtk_widget_set_size_request(button_start, 100, 50);
  gtk_widget_set_size_request(button_remember, 100, 50);
  gtk_widget_set_size_request(combo_box, 290, 50);
  gtk_widget_set_size_request(text_area, 600, 200);

  gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
  gtk_container_add(GTK_CONTAINER(window), widget_cord);

  gtk_fixed_put(GTK_FIXED(widget_cord), button_start, 540, 30);
  gtk_fixed_put(GTK_FIXED(widget_cord), button_remember, 20, 30);
  gtk_fixed_put(GTK_FIXED(widget_cord), combo_box, 140, 30);
  gtk_fixed_put(GTK_FIXED(widget_cord), text_area, 30, 120);

  g_signal_connect(button_start, "clicked", G_CALLBACK(click_imitation),
                   combo_box);
  g_signal_connect(button_remember, "clicked", G_CALLBACK(thread_input), NULL);
  gtk_widget_show_all(window);
}

void create_combo_box(GtkWidget *combo_box) {
  displays_id();
  gchar name[256] = {0};
  FILE *file = NULL;
  bool flag = open_fl_rplus("config/winname.dat", &file);
  flag = check_file(file);
  if (flag) {
    while (get_string(file, name, sizeof(name)))
      gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), name);
  }
  if (file) fclose(file);
}