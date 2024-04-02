#include "shapes.h"

LINE line_init(char* parameters) {
  LINE line;
  line.pos1.x = atoi(strtok(parameters, ","));
  line.pos1.y = atoi(strtok(NULL, ","));
  line.pos2.x = atoi(strtok(NULL, ","));
  line.pos2.y = atoi(strtok(NULL, ","));
  line.colour.r = atoi(strtok(NULL, ","));
  line.colour.g = atoi(strtok(NULL, ","));
  line.colour.b = atoi(strtok(NULL, ","));
  line.colour.a = atoi(strtok(NULL, ","));
  return line;
}

RECTANGLE rect_init(char* parameters) {
  RECTANGLE rect;
  rect.pos.x = atoi(strtok(parameters, ","));
  rect.pos.y = atoi(strtok(NULL, ","));
  rect.w = atoi(strtok(NULL, ","));
  rect.h = atoi(strtok(NULL, ","));
  rect.colour.r = atoi(strtok(NULL, ","));
  rect.colour.g = atoi(strtok(NULL, ","));
  rect.colour.b = atoi(strtok(NULL, ","));
  rect.colour.a = atoi(strtok(NULL, ","));
  return rect;
}

CIRCLE circ_init(char* parameters) {
  CIRCLE circ;
  circ.pos.x = atoi(strtok(parameters, ","));
  circ.pos.y = atoi(strtok(NULL, ","));
  circ.p = atoi(strtok(NULL, ","));
  circ.colour.r = atoi(strtok(NULL, ","));
  circ.colour.g = atoi(strtok(NULL, ","));
  circ.colour.b = atoi(strtok(NULL, ","));
  circ.colour.a = atoi(strtok(NULL, ","));
  return circ;
}

TRIANGLE tria_init(char* parameters) {
  TRIANGLE tria;
  tria.pos.x = atoi(strtok(parameters, ","));
  tria.pos.y = atoi(strtok(NULL, ","));
  tria.s = atoi(strtok(NULL, ","));
  tria.colour.r = atoi(strtok(NULL, ","));
  tria.colour.g = atoi(strtok(NULL, ","));
  tria.colour.b = atoi(strtok(NULL, ","));
  tria.colour.a = atoi(strtok(NULL, ","));
  return tria;
}

ROT_RECTANGLE rot_rect_init(char* parameters) {
  ROT_RECTANGLE rot_rect;
  rot_rect.angle = atoi(strtok(parameters, ","));
  rot_rect.pos.x = atoi(strtok(NULL, ","));
  rot_rect.pos.y = atoi(strtok(NULL, ","));
  rot_rect.w = atoi(strtok(NULL, ","));
  rot_rect.h = atoi(strtok(NULL, ","));
  rot_rect.colour.r = atoi(strtok(NULL, ","));
  rot_rect.colour.g = atoi(strtok(NULL, ","));
  rot_rect.colour.b = atoi(strtok(NULL, ","));
  rot_rect.colour.a = atoi(strtok(NULL, ","));
  return rot_rect;
}

// Bresenham, take this L
void create_line(LINE* line, IMAGE* img) {
  if (line->pos1.x > line->pos2.x) {
    POSITION temp = {line->pos1.x, line->pos1.y};
    line->pos1.x = line->pos2.x;
    line->pos1.y = line->pos2.y;
    line->pos2.x = temp.x;
    line->pos2.y = temp.y;
  }

  double slope = 0;
  double x = 0;
  if ((line->pos2.x - line->pos1.x) == 0) {
    slope = (double)(line->pos2.y - line->pos1.y) * -1;
    x = (double)line->pos1.x - 0.999;
  } else {
    slope = (double)(line->pos2.y - line->pos1.y) / (line->pos2.x - line->pos1.x);
    x = (double)line->pos1.x;
  }

  double kalkulaca = 0.999 / fabs(slope);
  double res = (fabs(slope) > 1) ? kalkulaca : 1;

  while (x <= (double)line->pos2.x) {
    double y = slope * (x - line->pos1.x) + line->pos1.y;
    POSITION pos = {x, y};
    draw_pixel(img, &pos, &line->colour);
    x += res;
  }
}

void create_rectangle(RECTANGLE* rect, IMAGE* img) {
  for (int y = rect->pos.y; y < (rect->pos.y + rect->h); y++) {
    for (int x = rect->pos.x; x < (rect->pos.x + rect->w); x++) {
      POSITION pos = {.x = x, .y = y};
      draw_pixel(img, &pos, &rect->colour);
    }
  }
}

void create_rotated_rectangle(ROT_RECTANGLE* rot_rect, IMAGE* img) {
  double angle_pi = rot_rect->angle / (180 / PI);
  for (int y = -rot_rect->h / 2; y < rot_rect->h / 2; y++) {
    for (int x = -rot_rect->w / 2; x < rot_rect->w / 2; x++) {
      POSITION pos = {.x = x * cos(angle_pi) - y * sin(angle_pi) + rot_rect->pos.x,
                      .y = y * cos(angle_pi) + x * sin(angle_pi) + rot_rect->pos.y};
      draw_pixel(img, &pos, &rot_rect->colour);
    }
  }
}

void create_triangle(TRIANGLE* tria, IMAGE* img) {
  double height = sqrt(pow(tria->s, 2) - pow(tria->s / 2, 2));
  double k = height / tria->s;
  int y_val = tria->pos.y - (height / 2);

  for (int y = -(1 - k) * height; y < k * height; y++) {
    int span = (tria->s / 2) - (height - y) * ((tria->s / 2) / height);
    for (int x = -span; x < span; x++) {
      POSITION pos = {.x = x + tria->pos.x,
                      .y = y + y_val};
      draw_pixel(img, &pos, &tria->colour);
    }
  }
}

// f(x) = sqrt( r^2 - x^2 )
void create_circle(CIRCLE* circ, IMAGE* img) {
  for (int y = -circ->p; y < circ->p; y++) {
    int span = (int)sqrt(pow(circ->p, 2) - pow(y, 2));
    for (int x = -span; x < span; x++) {
      POSITION pos = {.x = x + circ->pos.x,
                      .y = y + circ->pos.y};
      draw_pixel(img, &pos, &circ->colour);
    }
  }
}
