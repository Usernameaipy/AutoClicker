#include "file_rplus.h"

bool open_fl_rplus(const char *fl, FILE **file) {
  bool res = false;
  *file = fopen(fl, "r+");
  if ((*file) != NULL) {
    res = true;
  }
  return res;
}