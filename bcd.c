// Binary-coded decimal (unsigned)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bcd.h"
#include <stdbool.h>
#include "vec_macro.h"

VEC_CREATE(char)

enum eq {LT, EQ, GT};

bcd int_to_bcd(int n)
{
    bcd res = char_vinit(8);
    while (n)
    {
        char_push(res, n % 10);    
        n /= 10;
    }

    return res;
}

void print_bcd(bcd n)
{
    for (int i = n->size - 1; i >= 0; i--) {
        putchar(n->arr[i] + '0'); 
    }
    putchar('\n');
}

bcd bcd_add(bcd n1, bcd n2)
{
    bcd res = char_vinit(8);
    bcd arr[2] = {n1, n2};
    int large = (n1->size >= n2->size) ? 0 : 1;
    int small_len = (n1->size < n2->size) ? n1->size : n2->size;
    int large_len = (n1->size >= n2->size) ? n1->size : n2->size;
    char equal = n1->size == n2->size;
    char carry = 0;
    
    int i;
    for (i = 0; i < small_len; i++)
    {
        int curr_digit = n1->arr[i] + n2->arr[i] + carry;
        carry = 0;
        if (curr_digit > 9)
        {
            carry = 1;
            curr_digit %= 10;
        }
        char_push(res, curr_digit);
    }

    if (!equal)
    {
        while (i < large_len)
        {
            int curr_digit = arr[large]->arr[i] + carry;
            carry = 0;
            if (curr_digit > 9)
            {
                carry = 1;
                curr_digit %= 10;
            }
            char_push(res, curr_digit);
            i++;
        }

        if (carry)
        {
            char_push(res, carry);
        }
    }

    return res;
}

void bcd_free(bcd n)
{
    char_vfree(n);
}

bcd str_to_bcd(const char *str)
{
    int l = strlen(str);
    bcd res = char_vinit(8);

    for (int i = l-1; i >= 0; i--)
    {
        char_push(res, str[i] - '0') ;
    }

    return res;
}

bcd raw_int_to_bcd(int n) {
    bcd res = char_vinit(8);
    for (int i = 0; n > 0 && i < sizeof(int); i++) {
        char_push(res, n & 0xff);
        n = n >> 8; 
    }

    return res;
}

bool bcd_eq(bcd n1, bcd n2)
{
    if (n1->size != n2->size)
    {
        return false;
    }

    for (int i = 0; i < n1->size; i++)
    {
        if (n1->arr[i] != n2->arr[i])
        {
            return false; 
        } 
    }

    return true;
}

bool bcd_lt(bcd n1, bcd n2)
{
    if (n1->size > n2->size)
    {
        return false;
    } else if (n1->size < n2->size)
    {
        return true; 
    }

    int i;
    for (i = 0; i < n1->size; i++)
    {
        if (n1->arr[i] > n2->arr[i])
        {
            return false;
        } 
    }

    return (n1->arr[i] == n2->arr[i]) ? false : true;
}

bool bcd_le(bcd n1, bcd n2)
{
    if (n1->size > n2->size)
    {
        return false;
    } else if (n1->size < n2->size)
    {
        return true; 
    }

    int i;
    for (i = 0; i < n1->size; i++)
    {
        if (n1->arr[i] > n2->arr[i])
        {
            return false;
        } 
    }

    return true;
}

bool bcd_gt(bcd n1, bcd n2)
{
    return !(bcd_le(n1, n2));
}

bool bcd_ge(bcd n1, bcd n2)
{
    return !(bcd_lt(n1, n2));
}

void bcd_add_inplace(bcd n1, bcd n2)
{
    enum eq ord;
    if (n1->size < n2->size)
    {
        ord = LT;
    } else if (n1->size == n2->size)
    {
        ord = EQ; 
    } else
    {
        ord = GT; 
    }

    int least_size = (n1->size <= n2->size) ? n1->size : n2->size;
    int max_size = (n1->size <= n2->size) ? n2->size : n1->size;
    int carry = 0;
    int i;
    for (i = 0; i < least_size; i++)
    {
        n1->arr[i] += n2->arr[i] + carry;
        carry = 0;
        if (n1->arr[i] > 9)
        {
            carry = 1; 
            n1->arr[i] %= 10;
        }
    }

    if (ord != EQ)
    {
        for (; i < max_size; i++)
        {
            switch (ord)
            {
                case LT:
                {
                    int curr_dig = n2->arr[i] + carry;
                    carry = 0;
                    if (curr_dig > 9)
                    {
                        carry = 1; 
                        curr_dig %= 10;
                    }
                    char_push(n1, curr_dig);
                    break; 
                }
                case GT:
                {
                    n1->arr[i] += carry;
                    carry = 0;
                    if (n1->arr[i] > 9)
                    {
                        n1->arr[i] %= 10;
                        carry = 1; 
                    }
                }
            } 
        } 

        if (carry)
        {
            char_push(n1, carry); 
        }
    }
}
