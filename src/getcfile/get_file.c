#include "get_file.h"

bool get_file(size_t *value, const char *filename, size_t stdval) {
  bool res = false;
  FILE *file = NULL;
  if (open_fl_rplus(filename, &file)) {
    fscanf(file, "%lu", value);
    fclose(file);
    res = true;
  } else {
    file = fopen(filename, "w");
    if (file) {
      fprintf(file, "%lu", stdval);
      fclose(file);
      res = true;
    }
  }
  return res;
}

bool check_file(FILE *file) {
  bool ret = false;
  if (file != NULL) {
    long curs = ftell(file);
    int ch = fgetc(file);
    fseek(file, curs, SEEK_SET);
    ret = (ch != EOF) ? true : false;
  }
  return ret;
}

void change_entry(GtkEntry *entry, gpointer user_data) {
  FILE *file = NULL;
  const char *filename = (char *)user_data;
  if (open_fl_rplus(filename, &file)) {
    fclose(file);
    file = fopen(filename, "w");
    if (file) {
      fprintf(file, "%lu",
              (long unsigned)atoi((char *)gtk_entry_get_text(entry)));
      fclose(file);
    }
  } else {
    size_t temp;
    get_file(&temp, filename,
             (long unsigned)atoi((char *)gtk_entry_get_text(entry)));
  }
}
