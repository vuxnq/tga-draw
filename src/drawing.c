#include "drawing.h"

#include "shapes.h"
#include "utils.h"

void draw_line(char* parameters, IMAGE* img);
void draw_rectangle(char* parameters, IMAGE* img);
void draw_circle(char* parameters, IMAGE* img);
void draw_triangle(char* parameters, IMAGE* img);
void draw_rotated_rectangle(char* parameters, IMAGE* img);

void wrong_input_message(void);
void wrong_colour_message(void);

extern void handle_arguments(int argc, char** arguments, IMAGE* img) {
  if (argc != 7) {
    printf("! wrong parameters\n");
    printf("> usage:\t./program --output <filepath.tga> --width <number> --height <number>\n");
    exit(1);
  }

  for (int i = 1; i < argc - 1; i++) {
    if (!strcmp(arguments[i], "--output")) {
      if (!strncmp(strreverse(arguments[i + 1]), "agt.", 4))
        strcpy(img->output_path, strreverse(arguments[i + 1]));
      else {
        printf("! wrong output parameter\n");
        exit(1);
      }
    }
    if (!strcmp(arguments[i], "--width")) {
      if (atoi(arguments[i + 1]))
        img->width = atoi(arguments[i + 1]);
      else {
        printf("! wrong width parameter\n");
        exit(1);
      }
    }
    if (!strcmp(arguments[i], "--height")) {
      if (atoi(arguments[i + 1]))
        img->height = atoi(arguments[i + 1]);
      else {
        printf("! wrong height parameter\n");
        exit(1);
      }
    }
  }
}

void draw_pixel(IMAGE* img, POSITION* pos, COLOUR* colour) {
  if (pos->x >= 0 && pos->x < img->width && pos->y >= 0 && pos->y < img->height) {
    int pos_in_img = pos->y * img->width + pos->x;
    COLOUR og = {.r = img->canvas[pos_in_img].R,
                 .g = img->canvas[pos_in_img].G,
                 .b = img->canvas[pos_in_img].B};

    float alpha = (float)colour->a / 255;
    img->canvas[pos_in_img].R = alpha * colour->r + (1.0 - alpha) * og.r;
    img->canvas[pos_in_img].G = alpha * colour->g + (1.0 - alpha) * og.g;
    img->canvas[pos_in_img].B = alpha * colour->b + (1.0 - alpha) * og.b;
  }
}

extern void create_canvas(IMAGE* img) {
  FILE* output_file = fopen(img->output_path, "wb");
  TGA_HEADER header = {0, 0, 2, {0, 0, 0, 0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 24, 32};
  memcpy(header.width, &img->width, sizeof(header.width));
  memcpy(header.height, &img->height, sizeof(header.width));

  fwrite(&header, sizeof(header), 1, output_file);

  img->canvas = malloc(sizeof(RGB_PIXEL) * img->width * img->height);

  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      img->canvas[i * img->width + j].R = 0;
      img->canvas[i * img->width + j].G = 0;
      img->canvas[i * img->width + j].B = 0;
    }
  }
  fwrite(img->canvas, sizeof(RGB_PIXEL), img->width * img->height, output_file);

  fclose(output_file);
}

extern void paint_canvas(IMAGE* img) {
  FILE* output_file = fopen(img->output_path, "wb");

  TGA_HEADER header = {0, 0, 2, {0, 0, 0, 0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 24, 32};
  memcpy(header.width, &img->width, sizeof(header.width));
  memcpy(header.height, &img->height, sizeof(header.width));

  fwrite(&header, sizeof(header), 1, output_file);
  fwrite(img->canvas, sizeof(RGB_PIXEL), img->width * img->height, output_file);

  fclose(output_file);
}

extern void handle_input(char* radek, IMAGE* img) {
  const char delims[] = " \n";
  if (strcmp(radek, "\n")) {
    char* token = strtok(radek, delims);
    if (strncmp(token, "exit", 4)) {
      if (!strncmp(token, "line", 4)) {
        token = strtok(NULL, delims);
        if (token)
          draw_line(token, img);
        else
          wrong_input_message();
      } else if (!strncmp(token, "rectangle", 9)) {
        token = strtok(NULL, delims);
        if (token)
          draw_rectangle(token, img);
        else
          wrong_input_message();
      } else if (!strncmp(token, "circle", 6)) {
        token = strtok(NULL, delims);
        if (token)
          draw_circle(token, img);
        else
          wrong_input_message();
      } else if (!strncmp(token, "triangle", 8)) {
        token = strtok(NULL, delims);
        if (token)
          draw_triangle(token, img);
        else
          wrong_input_message();
      } else if (!strncmp(token, "rotated-rectangle", 17)) {
        token = strtok(NULL, delims);
        if (token)
          draw_rotated_rectangle(token, img);
        else
          wrong_input_message();
      } else if (!strncmp(token, "save", 4)) {
        printf("> saving image (%s)\n", img->output_path);
        paint_canvas(img);
      } else
        wrong_input_message();
    }
  } else
    printf("! missing input\n");
}

void draw_line(char* parameters, IMAGE* img) {
  if (check_params(parameters, 8)) {
    LINE line = line_init(parameters);
    if (check_colour(&line.colour)) {
      printf("> drawing line\n");
      create_line(&line, img);
    } else
      wrong_colour_message();
  } else
    wrong_input_message();
}

void draw_rectangle(char* parameters, IMAGE* img) {
  if (check_params(parameters, 8)) {
    RECTANGLE rect = rect_init(parameters);
    if (check_colour(&rect.colour)) {
      printf("> drawing rectangle\n");
      create_rectangle(&rect, img);
    } else
      wrong_colour_message();
  } else
    wrong_input_message();
}

void draw_circle(char* parameters, IMAGE* img) {
  if (check_params(parameters, 7)) {
    CIRCLE circ = circ_init(parameters);
    if (check_colour(&circ.colour)) {
      printf("> drawing circle\n");
      create_circle(&circ, img);
    } else
      wrong_colour_message();
  } else
    wrong_input_message();
}

void draw_triangle(char* parameters, IMAGE* img) {
  if (check_params(parameters, 7)) {
    TRIANGLE tria = tria_init(parameters);
    if (check_colour(&tria.colour)) {
      printf("> drawing triangle\n");
      create_triangle(&tria, img);
    } else
      wrong_colour_message();
  } else
    wrong_input_message();
}

void draw_rotated_rectangle(char* parameters, IMAGE* img) {
  if (check_params(parameters, 9)) {
    ROT_RECTANGLE rot_rect = rot_rect_init(parameters);
    if (check_colour(&rot_rect.colour)) {
      printf("> drawing rotated-rectangle\n");
      create_rotated_rectangle(&rot_rect, img);
    } else
      wrong_colour_message();
  } else
    wrong_input_message();
}

void wrong_input_message(void) {
  printf("! wrong input\n");
  printf("  available types: line, rectangle, circle, triangle, rotated-rectangle\n");
  printf("  usage:        line  <x1>,<y1>,<x2>,<y2>,<r>,<g>,<b>,<a>\n");
  printf("              circle  <x>,<y>,<p>,<r>,<g>,<b>,<a>\n");
  printf("            triangle  <x>,<y>,<s>,<r>,<g>,<b>,<a>\n");
  printf("           rectangle  <x>,<y>,<w>,<h>,<r>,<g>,<b>,<a>\n");
  printf("   rotated-rectangle  <angle>,<x>,<y>,<w>,<h>,<r>,<g>,<b>,<a>\n");
}

void wrong_colour_message(void) {
  printf("! <r> <g> <b> <a> values must be in range of 0 to 255\n");
}