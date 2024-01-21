#include "cat.h"
int main(int argc, char* argv[]) {
  struct Options options = {.number_lines = false,
                            .number_non_blank_lines = false,
                            .squeeze_blank_lines = false,
                            .show_ends = false,
                            .show_tabs = false,
                            .show_non_printing = false,
                            .line_number = 1};
  _parse_flags(argc, argv, &options);
  if (options.number_non_blank_lines) options.number_lines = false;
  _process_data(argc, argv, &options);
  return 0;
}

void _parse_flags(int argc, char* argv[], struct Options* options) {
  for (int i = 1; i < argc; i++) {
    int status = 1;
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j] != '\0' && status == 1; j++) {
        switch (argv[i][j]) {
          case 'n':
            options->number_lines = true;
            break;
          case 'b':
            options->number_non_blank_lines = true;
            break;
          case 's':
            options->squeeze_blank_lines = true;
            break;
          case 'e':
            options->show_non_printing = true;
            options->show_ends = true;
            break;
          case 'E':
            options->show_ends = true;
            break;
          case 't':
            options->show_non_printing = true;
            options->show_tabs = true;
            break;
          case 'T':
            options->show_tabs = true;
            break;
          case 'v':
            options->show_non_printing = true;
            break;
          case '-':
            if (strcmp("--number-nonblank", argv[i]) == 0) {
              options->number_non_blank_lines = true;
              status = 0;
            } else if (strcmp("--number", argv[i]) == 0) {
              options->number_lines = true;
              status = 0;
            } else if (strcmp("--squeeze-blank", argv[i]) == 0) {
              options->squeeze_blank_lines = true;
              status = 0;
            } else {
              fprintf(stderr, "cat: invalid option -- '%c'\n", argv[i][1]);
            }
            break;
          default:
            fprintf(stderr, "cat: invalid option -- '%c'\n", argv[i][1]);
        }
      }
    }
  }
}

void _process_data(int argc, char* argv[], struct Options* options) {
  bool isFileGiven = false;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      isFileGiven = true;
      FILE* fp = fopen(argv[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      } else {
        _output_data(fp, options);
        fclose(fp);
      }
    }
  }
  if (isFileGiven == false) {
    _output_data(stdin, options);
  }
}

void _output_data(FILE* fp, struct Options* options) {
  int cha;
  bool is_start_of_line = true;
  bool should_skip_empty_line = false;
  while ((cha = fgetc(fp)) != EOF) {
    unsigned char ch = (unsigned char)cha;
    if (is_start_of_line) {
      if (ch == '\n') {
        if (should_skip_empty_line == false) {
          if (options->number_lines) printf("%6d\t", options->line_number++);
          if (options->show_ends) printf("$");
          printf("\n");
        }
        if (options->squeeze_blank_lines && should_skip_empty_line == false) {
          should_skip_empty_line = true;
        }
      } else {
        if (options->number_lines || options->number_non_blank_lines)
          printf("%6d\t", options->line_number++);
        _print_character(ch, options);
        should_skip_empty_line = false;
        is_start_of_line = false;
      }
    } else {
      if (ch == '\n') {
        if (options->show_ends) printf("$");
        printf("\n");
        is_start_of_line = true;
      } else {
        is_start_of_line = false;
        _print_character(ch, options);
      }
    }
  }
}

void _print_character(unsigned char ch, struct Options* options) {
  if (options->show_non_printing) {
    if (ch >= 32) {
      if (ch < 127) {
        printf("%c", ch);
      } else if (ch == 127) {
        printf("^?");
      } else {
        printf("M-");
        if (ch >= 128 + 32) {
          if (ch < 128 + 127) {
            printf("%c", ch - 128);
          } else {
            printf("^?");
          }
        } else {
          printf("^%c", ch - 128 + 64);
        }
      }
    } else if (ch == '\t' && options->show_tabs == false) {
      printf("\t");
    } else {
      printf("^%c", ch + 64);
    }
  } else {
    if (options->show_tabs && ch == '\t') {
      printf("^%c", ch + 64);
    } else {
      printf("%c", ch);
    }
  }
}