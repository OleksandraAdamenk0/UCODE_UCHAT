#include "libmx.h"

/**
 * @NAME Push front
 * @DESCRIPTION Create a function that inserts a new node of t_list type
 * with the given parameter data at the beginning of the linked list. /n
 * @note \n
 */

void mx_push_front(t_list **list, void *data) {
    if (list == NULL) return;
    t_list *new_node = mx_create_node(data);
    if (new_node == NULL) return;
    new_node->next = *list;
    *list = new_node;
}
