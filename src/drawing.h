#pragma once
#include "utils.h"

typedef struct {
  byte id_length;
  byte color_map_type;
  byte image_type;
  byte color_map[5];
  byte x_origin[2];
  byte y_origin[2];
  byte width[2];
  byte height[2];
  byte depth;
  byte descriptor;
} TGA_HEADER;

typedef struct {
  byte B;
  byte G;
  byte R;
} RGB_PIXEL;

typedef struct {
  char output_path[MAX_LENGTH];
  int width;
  int height;
  RGB_PIXEL* canvas;
} IMAGE;

void handle_arguments(int argc, char** arguments, IMAGE* img);
void create_canvas(IMAGE* img);
void draw_pixel(IMAGE* img, POSITION* position, COLOUR* colour);
void paint_canvas(IMAGE* img);
void handle_input(char* radek, IMAGE* img);
