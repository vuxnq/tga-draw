#include "utils.h"

char* strreverse(char* str) {
  if (!str) return NULL;
  int i = 0;
  int j = strlen(str) - 1;
  while (i < j) {
    char c = str[i];
    str[i] = str[j];
    str[j] = c;
    i++;
    j--;
  }
  return str;
}

bool is_digit(char* string) {
  char digits[] = "0123456789";
  int i = 0;
  while (string[i] != '\0') {
    for (int j = 0; j < (int)strlen(digits); j++) {
      if (string[i] == digits[j])
        return true;
    }
    i++;
  }
  return false;
}

bool check_params(char* params, int count) {
  char params_c[MAX_LENGTH];
  strcpy(params_c, params);
  int count_check = 0;

  char* token = strtok(params_c, ",");
  while (token != NULL) {
    if (!is_digit(token))
      count_check--;

    token = strtok(NULL, ",");
    count_check++;
  }

  if (count_check != count)
    return false;
  else
    return true;
}

bool check_colour(COLOUR* colour) {
  if ((colour->r >= 0 && colour->r < 256) &&
      (colour->g >= 0 && colour->g < 256) &&
      (colour->b >= 0 && colour->b < 256) &&
      (colour->a >= 0 && colour->a < 256))
    return true;
  else
    return false;
}
