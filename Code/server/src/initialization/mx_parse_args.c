//
// Created by aleksa on 11/2/24.
//

#include "initialization.h"

t_arguments *mx_parse_args(int argc, const char *argv[]) {
  if (argc != 2 || !mx_is_numeric(argv[1])) return NULL;
  t_arguments *result = malloc(sizeof(t_arguments));
  result->port = mx_atoi(argv[1]);
  result->ip = "127.0.0.1";
  return result;
}
