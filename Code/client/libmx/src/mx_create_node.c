#include "libmx.h"

/**
 * @NAME Create node
 * @DESCRIPTION Create a function that
 * creates a new node of a linked list t_list.
 * The function assigns a parameter data to the list variable data
 * and assigns next to NULL.\n
 * @note \n
 */

t_list *mx_create_node(void *data) {
    t_list *node = (t_list *)malloc(sizeof(t_list));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}
