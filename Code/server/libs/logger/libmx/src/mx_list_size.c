#include "libmx.h"

/**
 * @NAME Size of list
 * @DESCRIPTION Create a function
 * that calculates the number of nodes in a linked list.
 * @RETURN Returns the amount of nodes in the linked list.
 * @note \n
 */

int mx_list_size(t_list *list){
    int size = 0;
    t_list *copy = list;
    for (; copy; copy = copy->next) size++;
    return size;
}
