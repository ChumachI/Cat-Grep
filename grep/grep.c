
#include "grep.h"
int main(int argc, char *argv[]) {
  struct Options options = {.ignore_case = false,
                            .inverse = false,
                            .show_num_of_matches = false,
                            .hide_file_name = false,
                            .show_index_of_line = false,
                            .only_file_name = false,
                            .suppress_no_such_file_error = false,
                            .is_template_found = false,
                            .print_only_match = false,
                            .num_of_templates = 0,
                            .num_of_files = 0,
                            .num_of_files_of_templates = 0,
                            .united_template = NULL};
  _parse_flags(argc, argv, &options);
  _read_template_files(&options);
  _parse_source_files(argc, argv, &options);
  _unite_templates(&options);
  _process_text_files(&options);
  _release_options(&options);
  return 0;
}

void _unite_templates(struct Options *options) {
  if (options->united_template == NULL)
    options->united_template = calloc(1, sizeof(char));
  for (int i = 0; i < options->num_of_templates; i++) {
    int u_temlate_size = strlen(options->united_template);
    int n_temlate_size = strlen(options->templates[i]);
    int new_size = (u_temlate_size + n_temlate_size) + 2;
    options->united_template =
        realloc(options->united_template, new_size * sizeof(char));
    if (i != 0) strcat(options->united_template, "|");
    strcat(options->united_template, options->templates[i]);
  }
}

void _parse_flags(int argc, char *argv[], struct Options *options) {
  int opt;
  struct option long_options[] = {{"file", required_argument, 0, 'f'},
                                  {"regexp", required_argument, 0, 'e'}};
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'e':
        _add_to_array(&options->templates, optarg, &options->num_of_templates);
        options->is_template_found = true;
        break;
      case 'i':
        options->ignore_case = true;
        break;
      case 'v':
        options->inverse = true;
        break;
      case 'c':
        options->show_num_of_matches = true;
        break;
      case 'l':
        options->only_file_name = true;
        break;
      case 'n':
        options->show_index_of_line = true;
        break;
      case 'h':
        options->hide_file_name = true;
        break;
      case 's':
        options->suppress_no_such_file_error = true;
        break;
      case 'f':
        _add_to_array(&options->files_of_templates, optarg,
                      &options->num_of_files_of_templates);
        break;
      case 'o':
        options->print_only_match = true;
        break;
      default:
        fprintf(stderr, "s21_grep: invalid option -- '%c'\n", opt);
    }
  }
}

void _read_template_files(struct Options *options) {
  for (int i = 0; i < options->num_of_files_of_templates; i++) {
    FILE *file;
    file = fopen(options->files_of_templates[i], "r");
    if (file == NULL) {
      if (options->suppress_no_such_file_error == false)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                options->files_of_templates[i]);
    } else {
      char *tmp = NULL;
      long unsigned int size = 0;
      while (getline(&tmp, &size, file) != -1) {
        int len = strlen(tmp);
        if (tmp[len - 1] == '\n') tmp[len - 1] = '\0';
        _add_to_array(&options->templates, tmp, &options->num_of_templates);
        options->is_template_found = true;
      }
      fclose(file);
      if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
      }
    }
  }
}

void _parse_source_files(int argc, char *argv[], struct Options *options) {
  for (int i = 1; i < argc; i++) {
    int len = strlen(argv[i]);
    if (strcmp(argv[i], "-ef") == 0) {
      _add_to_array(&options->files, argv[++i], &options->num_of_files);
    } else if (argv[i][0] == '-' &&
               (argv[i][len - 1] == 'f' || argv[i][len - 1] == 'e')) {
      i++;
    } else if (argv[i][0] == '-') {
      continue;
    } else if (options->is_template_found == false) {
      options->is_template_found = true;
      _add_to_array(&options->templates, argv[i], &options->num_of_templates);
    } else {
      _add_to_array(&options->files, argv[i], &options->num_of_files);
    }
  }
}

void _add_to_array(char ***arr_of_strings, char *str, int *num_of_strings) {
  char *new_string;
  asprintf(&new_string, "%s", str);
  char **new_arr_of_strings = malloc((*num_of_strings + 1) * sizeof(char *));
  for (int i = 0; i < *num_of_strings; i++) {
    new_arr_of_strings[i] = (*arr_of_strings)[i];
  }
  new_arr_of_strings[*num_of_strings] = new_string;
  free(*arr_of_strings);
  *arr_of_strings = new_arr_of_strings;
  *num_of_strings += 1;
}

struct Colors _get_colors() {
  struct stat file_stat;
  struct Colors colors;
  fstat(1, &file_stat);
  if (S_ISCHR(file_stat.st_mode)) {
    strcpy(colors.RED, "\033[1;91m");
    strcpy(colors.MAGENTA, "\033[35m");
    strcpy(colors.GREEN, "\033[32m");
    strcpy(colors.RESET, "\033[0m");
  } else {
    strcpy(colors.RED, "");
    strcpy(colors.MAGENTA, "");
    strcpy(colors.GREEN, "");
    strcpy(colors.RESET, "");
  }
  return colors;
}

void _release_options(struct Options *options) {
  for (int i = 0; i < options->num_of_files; i++) {
    if (options->files[i]) free(options->files[i]);
  }
  if (options->files) free(options->files);
  for (int i = 0; i < options->num_of_files_of_templates; i++) {
    if (options->files_of_templates[i]) free(options->files_of_templates[i]);
  }
  if (options->files_of_templates) free(options->files_of_templates);
  for (int i = 0; i < options->num_of_templates; i++) {
    if (options->templates[i]) free(options->templates[i]);
  }
  if (options->templates) free(options->templates);
  if (options->united_template) free(options->united_template);
}

void _process_text_files(struct Options *options) {
  for (int i = 0; i < options->num_of_files; i++) {
    FILE *file = fopen(options->files[i], "r");
    if (file == NULL) {
      if (options->suppress_no_such_file_error == false)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                options->files[i]);
    } else {
      if (options->only_file_name) {
        _flag_l(file, options, options->files[i]);
      } else if (options->show_num_of_matches) {
        _flag_c(file, options, options->files[i]);
      } else if (options->print_only_match && options->inverse == false) {
        _flag_o(file, options, options->files[i]);
      } else if (options->inverse && options->print_only_match == false) {
        _inverse_output(file, options, options->files[i]);
      } else if (options->inverse == false) {
        _default_output(file, options, options->files[i]);
      }
      fclose(file);
    }
  }
}

void _inverse_output(FILE *file, struct Options *options, char *file_name) {
  char *line = NULL;
  int num_of_line = 1;
  size_t size = 0;
  struct Colors colors = _get_colors();
  regex_t regex;
  regmatch_t match;
  int reg_opt = options->ignore_case ? REG_ICASE : 0;
  while ((getline(&line, &size, file) != -1)) {
    int newline_index = strcspn(line, "\n");
    if (newline_index < (int)strlen(line)) {
      line[newline_index] = '\0';
    }
    bool is_match = _check_line_for_match(line, options);
    if (is_match == false) {
      if (options->num_of_files > 1 && options->hide_file_name == false) {
        printf("%s%s:%s", colors.MAGENTA, file_name, colors.RESET);
      }
      if (options->show_index_of_line) {
        printf("%s%d%s:%s", colors.GREEN, num_of_line, colors.MAGENTA,
               colors.RESET);
      }
    }
    if (regcomp(&regex, options->united_template, reg_opt | REG_EXTENDED) !=
        0) {
      fprintf(stderr, "unable to compile regex: %s", options->united_template);
    } else {
      if ((regexec(&regex, line, 1, &match, 0)) != 0) {
        printf("%s\n", line);
      }
    }
    regfree(&regex);
    num_of_line++;
  }
  if (line) free(line);
}

void _print_prefix(struct Options *options, char *file_name, int num_of_line) {
  struct Colors colors = _get_colors();
  if (options->num_of_files > 1 && options->hide_file_name == false) {
    printf("%s%s:%s", colors.MAGENTA, file_name, colors.RESET);
  }
  if (options->show_index_of_line) {
    printf("%s%d%s:%s", colors.GREEN, num_of_line, colors.MAGENTA,
           colors.RESET);
  }
}

void _default_output(FILE *file, struct Options *options, char *file_name) {
  char *line = NULL;
  int num_of_line = 1;
  size_t size = 0;
  struct Colors colors = _get_colors();
  regex_t regex;
  regmatch_t match;
  int reg_opt = options->ignore_case ? REG_ICASE : 0;
  while ((getline(&line, &size, file) != -1)) {
    int newline_index = strcspn(line, "\n");
    if (newline_index < (int)strlen(line)) {
      line[newline_index] = '\0';
    }
    bool is_match = _check_line_for_match(line, options);
    if (is_match) {
      _print_prefix(options, file_name, num_of_line);
    }
    char *ptr = line;
    if (regcomp(&regex, options->united_template, reg_opt | REG_EXTENDED) !=
        0) {
      fprintf(stderr, "unable to compile regex: %s", options->united_template);
    } else {
      int status = 1;
      while (status) {
        int result = 1;
        if ((result = regexec(&regex, ptr, 1, &match, 0)) == 0) {
          printf("%.*s%s%.*s%s", (int)(match.rm_so), ptr, colors.RED,
                 (int)(match.rm_eo - match.rm_so), ptr + match.rm_so,
                 colors.RESET);
        } else {
          if (is_match) printf("%s\n", ptr);
          status = 0;
        }
        ptr += match.rm_eo;
      }
    }
    regfree(&regex);
    num_of_line++;
  }
  if (line) free(line);
}

void _flag_o(FILE *file, struct Options *options, char *file_name) {
  char *line = NULL;
  int num_of_line = 1;
  size_t size = 0;
  struct Colors colors = _get_colors();
  regex_t regex;
  regmatch_t match;
  int reg_opt = options->ignore_case ? REG_ICASE : 0;
  while ((getline(&line, &size, file) != -1)) {
    char *ptr = line;
    if (regcomp(&regex, options->united_template, reg_opt | REG_EXTENDED) !=
        0) {
      fprintf(stderr, "unable to compile regex: %s", options->united_template);
    } else {
      int status = 1;
      while (status) {
        if (regexec(&regex, ptr, 1, &match, 0) == 0) {
          _print_prefix(options, file_name, num_of_line);
          printf("%s%.*s%s\n", colors.RED, (int)(match.rm_eo - match.rm_so),
                 ptr + match.rm_so, colors.RESET);
        } else
          status = 0;
        ptr += match.rm_eo;
      }
    }
    regfree(&regex);
    num_of_line++;
  }
  if (line) free(line);
}

void _flag_c(FILE *file, struct Options *options, char *file_name) {
  char *line = NULL;
  size_t size = 0;
  int num_of_matches = 0;
  int num_of_mismatches = 0;
  struct Colors colors = _get_colors();
  while ((getline(&line, &size, file) != -1)) {
    bool is_match = _check_line_for_match(line, options);
    if (is_match)
      num_of_matches++;
    else
      num_of_mismatches++;
  }
  if (options->num_of_files > 1 && options->hide_file_name == false)
    printf("%s%s:%s", colors.MAGENTA, file_name, colors.RESET);
  if (options->inverse)
    printf("%d\n", num_of_mismatches);
  else
    printf("%d\n", num_of_matches);
  if (line) free(line);
}

void _flag_l(FILE *file, struct Options *options, char *file_name) {
  char *line = NULL;
  size_t size = 0;
  int status = 1;
  struct Colors colors = _get_colors();
  while (status && (getline(&line, &size, file) != -1)) {
    bool is_match = _check_line_for_match(line, options);
    if (is_match == !options->inverse) status = 0;
  }
  if (status == 0) printf("%s%s%s\n", colors.MAGENTA, file_name, colors.RESET);
  if (line) free(line);
}

bool _check_line_for_match(char *tmp, struct Options *options) {
  bool result = false;
  regex_t regex;
  int reg_opt = options->ignore_case ? REG_ICASE : 0;
  if (regcomp(&regex, options->united_template, reg_opt | REG_EXTENDED) != 0) {
    fprintf(stderr, "unable to compile regex: %s", options->united_template);
  } else {
    if (regexec(&regex, tmp, 0, NULL, 0) == 0) {
      result = true;
    }
    regfree(&regex);
  }
  return result;
}