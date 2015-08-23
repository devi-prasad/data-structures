#include <stddef.h>
#include <stdint.h>
#include<assert.h>
#include "slist.h"

void test_slist_generic()
{
    List alist = slist_new();
    List *list = &alist;

    assert(slist_length(list) == 0);

    slist_add_head(list, 10);
    slist_add_head(list, 20);
    
    assert(slist_length(list) == 2);
    assert(slist_lookup(list, 20));

    slist_add_tail(list, 30);
    slist_add_tail(list, 40);
    assert(slist_length(list) == 4);

    slist_delete_head(list);
    assert(slist_length(list) == 3);

    slist_delete_tail(list);
    assert(slist_length(list) == 2);

    slist_free(list);
    assert(slist_length(list) == 0);

    slist_delete_head(list);
    slist_delete_tail(list);
    slist_free(list);
    assert(slist_length(list) == 0);
}

int main()
{
    test_slist_generic();

    return 0;
}
