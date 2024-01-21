#ifndef GREP_H
#define GREP_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct Options {
  bool inverse;
  bool ignore_case;
  bool hide_file_name;
  bool only_file_name;
  bool print_only_match;
  bool is_template_found;
  bool show_index_of_line;
  bool show_num_of_matches;
  bool suppress_no_such_file_error;
  int num_of_files;
  int num_of_templates;
  int num_of_files_of_templates;
  char** files;
  char** templates;
  char** files_of_templates;
  char* united_template;
};
struct Colors {
  char RED[100];
  char GREEN[100];
  char RESET[100];
  char MAGENTA[100];
};
struct Colors _get_colors();
void _unite_templates(struct Options* options);
void _release_options(struct Options* options);
void _process_text_files(struct Options* options);
void _read_template_files(struct Options* options);
bool _check_line_for_match(char* tmp, struct Options* options);
void _flag_o(FILE* file, struct Options* options, char* file_name);
void _parse_flags(int argc, char* argv[], struct Options* options);
void _flag_l(FILE* file, struct Options* options, char* file_name);
void _flag_c(FILE* file, struct Options* options, char* file_name);
void _parse_source_files(int argc, char* argv[], struct Options* options);
void _add_to_array(char*** arr_of_strings, char* str, int* num_of_strings);
void _default_output(FILE* file, struct Options* options, char* file_name);
void _inverse_output(FILE* file, struct Options* options, char* file_name);
#endif
