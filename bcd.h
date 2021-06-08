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
void bcd_add_pow_inplace(bcd n1, bcd n2, int p);
void bcd_adi(bcd n1, int n2);
bool bcd_eq(bcd n1, bcd n2);
bool bcd_lt(bcd n1, bcd n2);
bool bcd_le(bcd n1, bcd n2);
bool bcd_gt(bcd n1, bcd n2);
bool bcd_ge(bcd n1, bcd n2);
bcd bcd_copy(bcd n);
bcd bcd_sub(bcd n1, bcd n2);
void bcd_sub_inplace(bcd n1, bcd n2);
bcd ten_comp(bcd n);
void bcd_unit_mul(bcd n1, char d);
bcd bcd_mul(bcd n1, bcd n2);
bcd bcd_div(bcd n1, bcd n2);
void bcd_inc(bcd n);

#endif
