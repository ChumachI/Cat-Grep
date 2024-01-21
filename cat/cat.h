#ifndef CAT_H
#define CAT_H
#endif
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
struct Options {
  bool number_lines;
  bool number_non_blank_lines;
  bool squeeze_blank_lines;
  bool show_ends;
  bool show_tabs;
  bool show_non_printing;
  int line_number;
};
void _output_data(FILE* fp, struct Options* options);
void _print_character(unsigned char c, struct Options* options);
void _parse_flags(int argc, char* argv[], struct Options* options);
void _process_data(int argc, char* argv[], struct Options* options);