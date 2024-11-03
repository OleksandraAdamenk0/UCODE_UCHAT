#include "libmx.h"

/**
 * @NAME Pop front
 * @DESCRIPTION Create a function that removes the first node of the linked list
 * and frees the memory allocated for the node.
 * @note \n
 */

void mx_pop_front(t_list **head) {
    if (head == NULL || *head == NULL) return;
    t_list *temp = *head;
    *head = (*head)->next;
    free(temp);
}
