#pragma once
#include "drawing.h"

typedef struct {
  POSITION pos1;
  POSITION pos2;
  COLOUR colour;
} LINE;

typedef struct {
  POSITION pos;
  int w, h;
  COLOUR colour;
} RECTANGLE;

typedef struct {
  POSITION pos;
  int p;
  COLOUR colour;
} CIRCLE;

typedef struct {
  POSITION pos;
  int s;
  COLOUR colour;
} TRIANGLE;

typedef struct {
  POSITION pos;
  double angle;
  int w, h;
  COLOUR colour;
} ROT_RECTANGLE;

LINE line_init(char* parameters);
RECTANGLE rect_init(char* parameters);
CIRCLE circ_init(char* parameters);
TRIANGLE tria_init(char* parameters);
ROT_RECTANGLE rot_rect_init(char* parameters);

void create_line(LINE* line, IMAGE* img);
void create_rectangle(RECTANGLE* rect, IMAGE* img);
void create_rotated_rectangle(ROT_RECTANGLE* rot_rect, IMAGE* img);
void create_triangle(TRIANGLE* tria, IMAGE* img);
void create_circle(CIRCLE* circ, IMAGE* img);
