#include "libmx.h"

/**
 * @NAME Push back
 * @DESCRIPTION Create a function that inserts a node of t_list type
 * with the given parameter data at the end of the linked list. /n
 * @note \n
 */

void mx_push_back(t_list **list, void *data) {
    if (list == NULL) return;
    t_list *new_node = mx_create_node(data);
    if (new_node == NULL) return;
    if (*list == NULL) {
        *list = new_node;
        return;
    }
    t_list *current = *list;
    while (current->next != NULL) current = current->next;
    current->next = new_node;
}
