//
// Created by aleksa on 11/2/24.
//

#include "initialization.h"

int mx_parse_args(int argc, const char * argv[]) {
  if (argc != 2 || !mx_is_numeric(argv[1])) return -1;
  return mx_atoi(argv[1]);
}
