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
    
    return 0;
}
