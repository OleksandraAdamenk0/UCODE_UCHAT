#include "libmx.h"

void mx_swap_list_node(t_list *node1, t_list *node2) {
    void *temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}
