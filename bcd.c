// Binary-coded decimal (unsigned)

#include <stdio.h>
#include <stdlib.h>
#include "vec_macro.h"
#include <string.h>
#include <assert.h>
#include "bcd.h"

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

int main(void)
{
    bcd n1 = str_to_bcd("123456789123456789");
    bcd n2 = str_to_bcd("123456789123456789");    
    bcd n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("987654321987654321987654321");
    n2 = str_to_bcd("98765987659876598765");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("1");
    n2 = str_to_bcd("256");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = int_to_bcd(1378420);
    print_bcd(n1);
    bcd_free(n1);

    n1 = raw_int_to_bcd(258);
    print_bcd(n1);
    bcd_free(n1);
    
    return 0;
}
