#include "libmx.h"

void mx_free_list(t_list **head) {
    if (head == NULL || *head == NULL) return;
    t_list *current = *head;
    t_list *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head = NULL;
}
