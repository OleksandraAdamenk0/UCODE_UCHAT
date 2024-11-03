#include "libmx.h"

/**
 * @NAME Sort list
 * @DESCRIPTION Create a function that
 * sorts a list's contents in ascending order.
 * The function cmp returns true if a > b
 * and false in other cases.
 * @RETURN Returns a pointer
 * to the first element of the sorted list.
 * @note \n
 */

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (lst == NULL || lst->next == NULL || cmp == NULL) return lst;
    bool sorted = false;
    t_list *temp;
    while (!sorted) {
        sorted = true;
        temp = lst;
        while (temp->next != NULL) {
            if (cmp(temp->data, temp->next->data)) {
                mx_swap_list_node(temp, temp->next);
                sorted = false;
            }
            temp = temp->next;
        }
    }
    return lst;
}
