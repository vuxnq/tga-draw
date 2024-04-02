#include "drawing.h"

int main(int argc, char** argv) {
  IMAGE img;
  handle_arguments(argc, argv, &img);
  create_canvas(&img);

  char radek[MAX_LENGTH] = {0};
  while (strncmp(radek, "exit", 4)) {
    fgets(radek, sizeof(radek), stdin);
    handle_input(radek, &img);
  }

  paint_canvas(&img);
  free(img.canvas);
  return 0;
}
