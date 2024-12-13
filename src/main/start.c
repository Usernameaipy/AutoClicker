#include "start.h"

int start(int argc, char *argv[]) {
  GtkApplication *app = gtk_application_new("com.example.GtkApplication",
                                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(an_activate), NULL);
  return g_application_run(G_APPLICATION(app), argc, argv);
}