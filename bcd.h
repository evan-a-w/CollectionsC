#ifndef BCD_H
#define BCD_H

#include <stdio.h>
#include <stdlib.h>
#include "vec_macro.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>

VEC_DEFINE(char)

typedef char_vec *bcd;

bcd int_to_bcd(int n);
void print_bcd(bcd n);
bcd bcd_add(bcd n1, bcd n2);
void bcd_free(bcd n);
bcd str_to_bcd(const char *str);
bcd raw_int_to_bcd(int n);
void bcd_add_inplace(bcd n1, bcd n2);
bool bcd_eq(bcd n1, bcd n2);
bool bcd_lt(bcd n1, bcd n2);
bool bcd_le(bcd n1, bcd n2);
bool bcd_gt(bcd n1, bcd n2);
bool bcd_ge(bcd n1, bcd n2);

#endif
