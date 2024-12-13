#include "get_id_name_win.h"

void displays_id(void) {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "ERROR DISPLAY\n");
    return;
  }

  FILE *id = fopen("config/id.dat", "w");
  FILE *winname = fopen("config/winname.dat", "w");
  Window root = DefaultRootWindow(display);
  Window parent;
  Window *children;
  unsigned int num_children;

  if (XQueryTree(display, root, &root, &parent, &children, &num_children)) {
    for (unsigned int i = 0; i < num_children; i++) {
      XWindowAttributes attrs;
      if (XGetWindowAttributes(display, children[i], &attrs) &&
          attrs.map_state == IsViewable) {
        char *window_name;
        if (XFetchName(display, children[i], &window_name)) {
          fprintf(id, "%lx\n", children[i]);
          fprintf(winname, "%s\n", window_name);
          XFree(window_name);
        } else {
          XClassHint *class_hint = XAllocClassHint();
          if (XGetClassHint(display, children[i], class_hint)) {
            fprintf(id, "%lx\n", children[i]);
            fprintf(
                winname, "%s\n",
                class_hint->res_class ? class_hint->res_class : "(no name)");
            XFree(class_hint->res_name);
            XFree(class_hint->res_class);
            XFree(class_hint);
          } else {
            fprintf(id, "%lx\n", children[i]);
            fprintf(winname, "(no name)\n");
          }
        }
      }
    }
    XFree(children);
  } else {
    fprintf(stderr, "ERROR WINDOW LIST\n");
  }

  if (id) fclose(id);
  if (winname) fclose(winname);
  XCloseDisplay(display);
}