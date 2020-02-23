#include "list.h"

int main(){
    printf("running main\n");
    struct list* l = list_create();
    printf("running main\n");
    list_insert(l, 1);
    printf("running main\n");
    list_insert(l, 1);
    list_insert(l, 1);
    list_insert(l, 1);
    list_insert(l, 1);
    list_insert(l, 1);
    list_print(l);
    list_reverse(l);
    list_print(l);
    list_free(l);
    return 0;
}