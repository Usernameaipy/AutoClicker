#include "gtk_application.h"

void an_activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "MyClicker");
  GtkWidget *button_start = gtk_button_new_with_label("Start");
  GtkWidget *button_remember = gtk_button_new_with_label("Remem");
  GtkWidget *text_area = gtk_text_view_new();
  GtkWidget *combo_box = gtk_combo_box_text_new();
  GtkWidget *widget_cord = gtk_fixed_new();
  GtkEntry *conf_one = GTK_ENTRY(gtk_entry_new());
  GtkEntry *conf_two = GTK_ENTRY(gtk_entry_new());
  GtkEntry *conf_three = GTK_ENTRY(gtk_entry_new());
  GtkWidget *label_one = gtk_label_new("Time:");
  GtkWidget *label_two = gtk_label_new("Repets:");
  GtkWidget *label_three = gtk_label_new("Quantity:");
  gtk_window_set_default_size(GTK_WINDOW(window), 420, 290);
  create_combo_box(combo_box);
  gtk_widget_set_size_request(button_start, 180, 60);
  gtk_widget_set_size_request(button_remember, 180, 60);
  gtk_widget_set_size_request(combo_box, 290, 60);
  gtk_entry_set_width_chars(conf_one, 10);
  gtk_entry_set_width_chars(conf_two, 10);
  gtk_entry_set_width_chars(conf_three, 10);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_add(GTK_CONTAINER(window), widget_cord);
  gtk_fixed_put(GTK_FIXED(widget_cord), label_one, 22, 110);
  gtk_fixed_put(GTK_FIXED(widget_cord), GTK_WIDGET(conf_one), 22, 140);
  gtk_fixed_put(GTK_FIXED(widget_cord), label_two, 161, 110);
  gtk_fixed_put(GTK_FIXED(widget_cord), GTK_WIDGET(conf_two), 161, 140);
  gtk_fixed_put(GTK_FIXED(widget_cord), label_three, 300, 110);
  gtk_fixed_put(GTK_FIXED(widget_cord), GTK_WIDGET(conf_three), 300, 140);
  gtk_fixed_put(GTK_FIXED(widget_cord), button_start, 218, 210);
  gtk_fixed_put(GTK_FIXED(widget_cord), button_remember, 22, 210);
  gtk_fixed_put(GTK_FIXED(widget_cord), combo_box, 22, 30);
  g_signal_connect(button_start, "clicked", G_CALLBACK(click_imitation),
                   combo_box);
  g_signal_connect(button_remember, "clicked", G_CALLBACK(thread_input), NULL);
  g_signal_connect(conf_three, "changed", G_CALLBACK(change_entry),
                   "config/qclick.conf");
  g_signal_connect(conf_one, "changed", G_CALLBACK(change_entry),
                   "config/time.conf");
  g_signal_connect(conf_two, "changed", G_CALLBACK(change_entry),
                   "config/qrepets.conf");
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