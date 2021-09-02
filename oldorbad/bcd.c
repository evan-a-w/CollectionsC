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
    }

    if (carry)
    {
        char_push(res, carry);
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

    return (n1->arr[i-1] == n2->arr[i-1]) ? false : true;
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
    }

    if (carry)
    {
        char_push(n1, carry); 
    }
}

void bcd_sub_inplace(bcd n1, bcd n2)
{
    if (bcd_lt(n1, n2))
    {
        printf("Can't have negative result for subtraction.\n");
        return;
    }
    
    for (int i = 0; i < n2->size; i++)
    {
        n1->arr[i] -= n2->arr[i];
        if (n1->arr[i] < 0)
        {
            n1->arr[i] += 10;
            int y = i+1;
            while (!n1->arr[y]) y++;
            n1->arr[y]--;
            for (y--; y > i; y--)
            {
                n1->arr[y] = 9; 
            }
        } 
    }

    while (n1->size > 1 && !n1->arr[n1->size - 1])
    {
        char_pop(n1); 
    }
}

bcd bcd_copy(bcd n)
{
    bcd res = char_vinit(8);
    for (int i = 0; i < n->size; i++)
    {
        char_push(res, n->arr[i]); 
    }

    return res;
}

bcd bcd_sub(bcd n1, bcd n2)
{
    bcd res = bcd_copy(n1);
    bcd_sub_inplace(res, n2);
    return res;
}

void bcd_adi(bcd n1, int n2)
{
    bcd b2 = int_to_bcd(n2);
    bcd_add_inplace(n1, b2);
    bcd_free(b2);
}

void bcd_add_pow_inplace(bcd n1, bcd n2, int p)
{
    int n2s = n2->size + p;
    enum eq ord;
    if (n1->size < n2s)
    {
        ord = LT;
    } else if (n1->size == n2s)
    {
        ord = EQ; 
    } else
    {
        ord = GT; 
    }

    int least_size = (n1->size <= n2s) ? n1->size : n2s;
    int max_size = (n1->size <= n2s) ? n2s : n1->size;
    int carry = 0;
    int i;
    for (i = 0; i < least_size; i++)
    {
        char cn2 = (i + 1  <= p) ? 0 : n2->arr[i-p];
        n1->arr[i] += cn2 + carry;
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
                    char cn2 = (i + 1  <= p) ? 0 : n2->arr[i-p];
                    int curr_dig = cn2 + carry;
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
    }

    if (carry)
    {
        char_push(n1, carry); 
    }
}

void bcd_unit_mul(bcd n1, char d)
{
    int carry = 0;
    for (int i = 0; i < n1->size; i++)
    {
        n1->arr[i] *= d;
        n1->arr[i] += carry; 
        carry = 0;
        if (n1->arr[i] > 9)
        {
            carry = n1->arr[i] / 10;
            n1->arr[i] %= 10; 
        }
    }

    if (carry)
    {
        char_push(n1, carry);
    }
}

bcd bcd_mul(bcd n1, bcd n2)
{
    bcd res = int_to_bcd(0);
    for (int i = 0; i < n2->size; i++)
    {
        bcd tmp = bcd_copy(n1); 
        bcd_unit_mul(tmp, n2->arr[i]);
        bcd_add_pow_inplace(res, tmp, i);
        bcd_free(tmp);
    }

    return res;
}

void bcd_inc(bcd n)
{
    int carry = 1;
    int i = 0;
    while (i < n->size && carry)
    {
        n->arr[i] += carry;
        carry = 0;
        if (n->arr[i] > 9)
        {
            n->arr[i] %= 10;
            carry = 1;
        }
        i++; 
    }
    if (carry)
    {
        char_push(n, carry); 
    }
}

bcd bcd_div(bcd n1, bcd n2)
{
    if (bcd_lt(n1, n2))
    {
        return 0; 
    }

    bcd cn1 = bcd_copy(n1);
    bcd i = int_to_bcd(0);
    // need to increase the power of n2 until its more so its faster

    while (bcd_ge(cn1, n2))
    {
        bcd_sub_inplace(cn1, n2);
        bcd_inc(i);
    }

    bcd_free(cn1);
    return i;
}
