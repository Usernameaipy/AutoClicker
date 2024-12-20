#include "clicer.h"

void click_imitation(GtkWidget *button, gpointer user_data) {
  GtkWidget *combo_box = GTK_WIDGET(user_data);
  unsigned int id =
      get_winid(gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box)));
  Window target_window = id;
  size_t time = 0, quantity = 0;
  get_file(&time, "config/time.conf", 1);
  get_file(&quantity, "config/qrepets.conf", 60);
  thread_param *param = g_new(thread_param, 1);
  *param = (thread_param){
      .target_window = target_window, .time = time, .quantity = quantity};
  g_thread_new("clicker", thread_click, (gpointer)param);
}

void *thread_click(gpointer user_data) {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "ERROR DISPLAY");
    return NULL;
  }
  thread_param *parametr = (thread_param *)user_data;
  Window target_window = (Window)parametr->target_window;
  size_t time = parametr->time;
  size_t quantity = parametr->quantity;
  for (size_t i = 0; i < quantity; i++) {
    for (size_t j = 0; j < get_len_now(); j++) {
      user_click *temp = (user_click *)malloc(sizeof(user_click));
      get_user_clic(temp);
      if (temp) {
        if (temp->type == actions_key) {
          char str[2];
          str[0] = temp->keyboard.key;
          str[1] = '\0';
          KeyCode keycode = XKeysymToKeycode(display, XStringToKeysym(str));
          XSetInputFocus(display, target_window, RevertToPointerRoot,
                         CurrentTime);
          XFlush(display);
          XTestFakeKeyEvent(display, keycode, True, 0);
          XFlush(display);
          XTestFakeKeyEvent(display, keycode, False, 0);
          XFlush(display);
          g_usleep(time * 1000000);
        } else if (temp->type == actions_mouse) {
          XSetInputFocus(display, target_window, RevertToPointerRoot,
                         CurrentTime);
          XFlush(display);
          int x = temp->mouse.x;
          int y = temp->mouse.y;
          XTestFakeMotionEvent(display, 0, x, y, CurrentTime);
          XFlush(display);
          XTestFakeButtonEvent(display, 1, TRUE, CurrentTime);
          XFlush(display);
          XTestFakeButtonEvent(display, 1, FALSE, CurrentTime);
          XFlush(display);
          g_usleep(time * 1000000);
        }
      }
      if (temp) free(temp);
    }
  }
  clicks_free();
  if (display) XCloseDisplay(display);
  g_free(parametr);
  return NULL;
}

unsigned int get_winid(gint pos) {
  FILE *file = NULL;
  bool flag = open_fl_rplus("config/id.dat", &file);
  if (flag) flag = check_file(file);
  unsigned int res;
  if (flag) {
    for (int i = 0; i < (int)pos + 1 && flag != false; i++)
      if (fscanf(file, "%x", &res) != 1) flag = false;
  }
  if (file != NULL) fclose(file);
  return res;
}

bool get_string(FILE *file, char *string, size_t len) {
  bool flag = false;
  if (fgets(string, len, file)) flag = true;
  return flag;
}