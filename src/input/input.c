#include "input.h"

static struct {
  user_click *user_clicks;
  size_t now_len;
  size_t len;
  size_t getting;
} clicks_stru;

bool clicks_alloc(size_t len) {
  bool flag = false;
  if (clicks_stru.user_clicks == NULL) flag = true;
  if (flag) {
    clicks_stru.user_clicks = (user_click *)malloc(sizeof(user_click) * len);
    if (clicks_stru.user_clicks == NULL)
      flag = false;
    else {
      clicks_stru.len = len;
      clicks_stru.now_len = 0;
      clicks_stru.getting = 0;
    }
  }
  return flag;
}

bool clicks_free(void) {
  bool flag = false;
  if (clicks_stru.user_clicks != NULL) flag = true;
  if (flag) {
    free(clicks_stru.user_clicks);
    clicks_stru.len = 0;
    clicks_stru.now_len = 0;
    clicks_stru.getting = 0;
    clicks_stru.user_clicks = NULL;
  }
  return flag;
}

bool reclicks_alloc(size_t new_len) {
  bool flag = false;
  if (clicks_stru.user_clicks != NULL && new_len > clicks_stru.len) flag = true;
  if (flag) {
    user_click *temp =
        (user_click *)malloc(sizeof(user_click) * clicks_stru.len);
    if (temp) {
      size_t now_len = clicks_stru.now_len;
      for (size_t i = 0; i < clicks_stru.len; i++) {
        cp_user_click(&clicks_stru.user_clicks[i], &temp[i]);
      }
      clicks_free();
      clicks_alloc(new_len);
      for (size_t i = 0; i < clicks_stru.len; i++) {
        cp_user_click(&temp[i], &clicks_stru.user_clicks[i]);
      }
      free(temp);
      clicks_stru.now_len = now_len;
    } else
      flag = false;
  }
  return flag;
}

void cp_user_click(user_click *elem, user_click *target) {
  if (elem->type == actions_mouse) {
    target->type = actions_mouse;
    target->mouse.x = elem->mouse.x;
    target->mouse.y = elem->mouse.y;
  } else {
    target->type = actions_key;
    target->keyboard.key = elem->keyboard.key;
  }
}

bool click_add(user_click *click) {
  bool flag = false;
  if (clicks_stru.user_clicks) flag = true;
  if (flag) {
    if (clicks_stru.now_len < clicks_stru.len) {
      cp_user_click(click, &clicks_stru.user_clicks[clicks_stru.now_len]);
      clicks_stru.now_len += 1;
    } else {
      if (reclicks_alloc(clicks_stru.len * 2)) {
        cp_user_click(click, &clicks_stru.user_clicks[clicks_stru.now_len]);
        clicks_stru.now_len += 1;
      } else
        flag = false;
    }
  }
  return flag;
}

void get_quan(size_t *quantity) {
  FILE *file_conf = NULL;
  bool flag = open_fl_rplus("config/setquantity.conf", &file_conf);
  if (!flag) {
    flag = create_file_conf_q();
    flag = open_fl_rplus("config/setquantity.conf", &file_conf);
  }
  if (flag) {
    fscanf(file_conf, "%lu\n", quantity);
  }
  if (file_conf) fclose(file_conf);
}

bool create_file_conf_q(void) {
  bool flag = false;
  FILE *file = NULL;
  size_t quantity = 10;
  file = fopen("config/setquantity.conf", "w");
  if (file) flag = true;
  if (flag) {
    fprintf(file, "%lu\n", quantity);
  }
  fclose(file);
  return flag;
}

size_t get_len_now(void) { return clicks_stru.now_len; }

void record_mouse_click(Display *display, XEvent *event) {
  if (clicks_stru.len > clicks_stru.now_len) {
    user_click *temp = (user_click *)malloc(sizeof(user_click));
    if (temp) {
      temp->type = actions_mouse;
      temp->mouse.x = event->xbutton.x;
      temp->mouse.y = event->xbutton.y;
      click_add(temp);
    }
    if (temp) free(temp);
  }
}

void record_key_press(Display *display, XEvent *event) {
  if (clicks_stru.len > clicks_stru.now_len) {
    user_click *temp = (user_click *)malloc(sizeof(user_click));
    if (temp) {
      temp->type = actions_key;
      temp->keyboard.key = (KeyCode)XLookupKeysym(&event->xkey, 0);
      click_add(temp);
    }
    if (temp) free(temp);
  }
}

void *input_click(void *f) {
  Display *display = XOpenDisplay(NULL);
  int screen = DefaultScreen(display);
  int screen_width = DisplayWidth(display, screen);
  int screen_height = DisplayHeight(display, screen);
  Window window = XCreateSimpleWindow(
      display, RootWindow(display, screen), 0, 0, screen_width, screen_height,
      0, BlackPixel(display, screen), WhitePixel(display, screen));
  XSelectInput(display, window, ButtonPressMask | KeyPressMask);
  XMapWindow(display, window);
  XFlush(display);
  size_t quantity;
  get_quan(&quantity);
  clicks_alloc(quantity);
  XEvent event;
  while (get_len_now() < quantity) {
    XNextEvent(display, &event);
    if (event.type == ButtonPress) {
      record_mouse_click(display, &event);
    }
    if (event.type == KeyPress) {
      record_key_press(display, &event);
    }
  }
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return NULL;
}

void thread_input(void) { g_thread_new("input", input_click, NULL); }

void get_user_clic(user_click *temp) {
  if (clicks_stru.getting >= clicks_stru.now_len) clicks_stru.getting = 0;
  if (clicks_stru.getting < clicks_stru.now_len) {
    cp_user_click(&clicks_stru.user_clicks[clicks_stru.getting], temp);
    clicks_stru.getting += 1;
  }
}

void arr_print(void) {
  for (size_t i = 0; i < clicks_stru.len; i++) {
    if (clicks_stru.user_clicks[i].type == actions_key) {
      g_print("%d\n", clicks_stru.user_clicks[i].keyboard.key);
    } else
      g_print("%d %d\n", clicks_stru.user_clicks[i].mouse.x,
              clicks_stru.user_clicks[i].mouse.y);
  }
}