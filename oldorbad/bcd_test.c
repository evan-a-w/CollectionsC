#include "bcd.h"
#include <assert.h>

int main(void)
{
    bcd n1 = str_to_bcd("123456789123456789");
    bcd n2 = str_to_bcd("123456789123456789");    
    bcd n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_add_inplace(n1, n2);
    assert(bcd_eq(n1,n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("987654321987654321987654321");
    n2 = str_to_bcd("98765987659876598765");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_add_inplace(n1, n2);
    assert(bcd_eq(n1,n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("1");
    n2 = str_to_bcd("256");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_add_inplace(n1, n2);
    assert(bcd_eq(n1,n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = int_to_bcd(1378420);
    print_bcd(n1);

    n2 = raw_int_to_bcd(258);
    print_bcd(n2);

    assert(!bcd_eq(n1, n2));
    bcd_free(n1);
    bcd_free(n2);

    n1 = str_to_bcd("987654321987654321987654321");
    n2 = str_to_bcd("98765987659876598765");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_add_inplace(n1, n2);
    assert(bcd_eq(n1,n3));
    bcd_sub_inplace(n1, n2);
    bcd n4 = str_to_bcd("987654321987654321987654321");
    assert(bcd_eq(n1,n4));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    n1 = str_to_bcd("987654321987654321987654321");
    n2 = str_to_bcd("98765987659876598765");
    n3 = bcd_add(n1, n2);
    print_bcd(n3);
    bcd_add_inplace(n2, n1);
    assert(bcd_eq(n2,n3));
    bcd_sub_inplace(n2, n1);
    n4 = str_to_bcd("98765987659876598765");
    assert(bcd_eq(n2,n4));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);
    
    n1 = str_to_bcd("12345");
    n2 = str_to_bcd("12345");
    assert(!bcd_lt(n1, n2));
    assert(bcd_eq(n1, n2));
    assert(bcd_ge(n1, n2));
    assert(bcd_le(n1, n2));
    assert(!bcd_gt(n1, n2));
    n3 = str_to_bcd("0");
    n4 = bcd_sub(n1, n2);
    bcd_sub_inplace(n1, n2);
    print_bcd(n1);
    print_bcd(n4);
    assert(bcd_eq(n1, n4));
    assert(bcd_eq(n1,n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    n1 = str_to_bcd("689");
    n2 = str_to_bcd("420");
    n3 = str_to_bcd("1109");
    bcd_add_inplace(n1, n2);
    assert(bcd_eq(n1, n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("689");
    n2 = str_to_bcd("420");
    n3 = str_to_bcd("1109");
    n4 = bcd_add(n1, n2);
    assert(bcd_eq(n4, n3));
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    printf("Onto pow adds\n");
    n1 = str_to_bcd("689");
    n2 = str_to_bcd("42");
    n3 = str_to_bcd("1109");
    bcd_add_pow_inplace(n1, n2, 1);
    assert(bcd_eq(n1, n3));
    printf("p1\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("689");
    n2 = str_to_bcd("42");
    n3 = str_to_bcd("731");
    bcd_add_pow_inplace(n1, n2, 0);
    assert(bcd_eq(n1, n3));
    printf("p2\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    n1 = str_to_bcd("689");
    n2 = str_to_bcd("42");
    n3 = str_to_bcd("4889");
    bcd_add_pow_inplace(n1, n2, 2);
    assert(bcd_eq(n1, n3));
    printf("p3\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);

    printf("Unit mul:\n");
    n1 = str_to_bcd("489");
    char d = 3;
    n3 = str_to_bcd("1467");
    bcd_unit_mul(n1, d);
    assert(bcd_eq(n1, n3));
    print_bcd(n1);
    printf("p1\n");
    bcd_free(n1);
    bcd_free(n3);

    printf("Mul:\n");
    n1 = str_to_bcd("689");
    n2 = str_to_bcd("42");
    n3 = str_to_bcd("28938");
    n4 = bcd_mul(n1, n2);
    assert(bcd_eq(n4, n3));
    printf("p1\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    n1 = str_to_bcd("689");
    n3 = str_to_bcd("474721");
    n4 = bcd_mul(n1, n1);
    assert(bcd_eq(n4, n3));
    printf("p2\n");
    bcd_free(n1);
    bcd_free(n3);
    bcd_free(n4);

    n1 = str_to_bcd("689");
    n2 = str_to_bcd("13694");
    n3 = str_to_bcd("9435166");
    n4 = bcd_mul(n1, n2);
    assert(bcd_eq(n4, n3));
    printf("p3\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    n1 = str_to_bcd("123456789");
    n2 = str_to_bcd("246810246810246810");
    n3 = str_to_bcd("30470400563490563460093090");
    n4 = bcd_mul(n1, n2);
    assert(bcd_eq(n3, n4));
    printf("p4\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n4);

    printf("Div\n");
    n1 = str_to_bcd("123456789");
    n2 = str_to_bcd("246810246810246810");
    n3 = str_to_bcd("1999163017");
    n4 = bcd_div(n2, n1);
    assert(bcd_eq(n3, n4));
    printf("p1\n");
    bcd_free(n1);
    bcd_free(n2);
    bcd_free(n3);
    bcd_free(n4);

    return 0;
}
