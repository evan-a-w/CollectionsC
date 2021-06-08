#include <stdio.h>
#include <stdlib.h>
#include "vec_macro.h"
#include <string.h>
#include <assert.h>

VEC_CREATE(char)

typedef char_vec *bcd;

bcd int_to_bcd(int n);
void print_bcd(bcd n);
bcd bcd_add(bcd n1, bcd n2);
void bcd_free(bcd n);
bcd str_to_bcd(const char *str);
bcd raw_int_to_bcd(int n);
