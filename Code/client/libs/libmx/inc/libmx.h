#ifndef LIBMX_H
#define LIBMX_H

#include <unistd.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>

// Structures
// ==================================================================

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

// Additional functions
// ==================================================================

bool mx_is_numeric(const char *str);

void mx_printerr(const char *s);

/**
* @NAME Additional function
* @DESCRIPTION The `mx_atoi` function takes a string containing digits
* and converts it into an integer (`int`).
* It accounts for an optional leading sign (`+` or `-`) at the beginning
* of the number.
* @RETURN The integer value represented by the number in the `str` string
* @note Very useful function for processing command-line arguments,
which will be helpful in future tasks and for users of the library \n
*/
int mx_atoi(const char* str);


/**
* @NAME mx_isspace
* @DESCRIPTION The `mx_isspace` function checks if a given character
* is a whitespace character. This includes space (' '), tab ('\t'),
* newline ('\n'), carriage return ('\r'), vertical tab ('\v'), and
* form feed ('\f').
* @RETURN `true` if `c` is a whitespace character, otherwise `false`.
* @note This function is useful because
* it is utilized by several other functions.
*/
bool mx_isspace(char c);

/**
* @NAME mx_swap_list_node
* @DESCRIPTION The `mx_swap_list_node` function swaps the data pointers of
* two linked list nodes. This operation does not move the nodes but
* rather exchanges their contents.
* @RETURN Void. The function modifies the input nodes in place.
* @note Can be used for reordering elements in a list without reallocating memory,
* which is efficient for in-place sorting.
*/
void mx_swap_list_node(t_list *node1, t_list *node2);

/**
* @NAME mx_char_to_str
* @DESCRIPTION The `mx_char_to_str` function creates a new dynamically
* allocated string containing a single character.
* @RETURN Pointer to a newly allocated string with the character `c`.
* If allocation fails, returns `NULL`.
* @note Helpful when converting characters to strings for concatenation,
* formatting, or string manipulation operations.
*/
char *mx_char_to_str(char c);

/**
* @NAME mx_free_list
* @DESCRIPTION The `mx_free_list` function deallocates memory for each node
* in a linked list, starting from the given head, and sets the head pointer
* to `NULL`.
* @RETURN Void. The function modifies the list in place by freeing each node
* and clearing the head pointer.
* @note Essential for freeing memory in dynamically allocated linked lists
* to prevent memory leaks.
*/
void mx_free_list(t_list **head);

// Utils pack
// ==================================================================

/**
 * @NAME Print character
 * @DESCRIPTION Create a function that outputs a single character to the standard output.
 * @note \n
 */
void mx_printchar(char c);

/**
 * @NAME Print multibyte characters
 * @DESCRIPTION Create a function that outputs ASCII
 * and multibyte characters to the standard output.
 * @note \n
 */
void mx_print_unicode(wchar_t c);

/**
 * @NAME Print string
 * @DESCRIPTION Create a function that
 * outputs a string of characters to the standard output.
 * @note \n
 */
void mx_printstr(const char *s);

/**
 * @NAME Print array of strings
 * @DESCRIPTION Create a function that outputs: \n
 * - an array of strings "arr" to the standard output with a delimiter
 * "delim" between the elements of an array \n
 * - nothing if "arr" or "delim" do not exist \n
 * - a newline at the end of the output "arr" must be NULL-terminated,
 * in other cases the behavior is undefined.
 * @note \n
 */
void mx_print_strarr(char **arr, const char *delim);

/**
 * @NAME Print integer
 * @DESCRIPTION Create a function that
 * outputs integer values to the standard output.
 * @note \n
 */
void mx_printint(int n);

/**
 * @NAME Exponentiation
 * @DESCRIPTION Create a function that computes "n"
 * raised to the power of zero or a positive integer "pow".
 * @RETURN Returns the result of "n" to the power of "pow".
 * @note \n
 */
double mx_pow(double n, unsigned int pow);

/**
* @NAME Square root
* @DESCRIPTION Create a function that computes
 * the non-negative square root of "x". \n
* The function must compute square root in less than 2 seconds.
* @RETURN Returns the square root of the number "x"
* if it is natural, and 0 otherwise.
* @note \n
*/
int mx_sqrt(int x);

/**
* @NAME Decimal to hex
* @DESCRIPTION Create a function that converts an unsigned long number
 * into a hexadecimal string.
* @RETURN Returns the number converted to a hexadecimal string.
* @note \n
*/
char *mx_nbr_to_hex(unsigned long nbr);

/**
 * @NAME Hex to decimal
 * @DESCRIPTION Create a function that converts a hexadecimal string
 * into an unsigned long number.
 * @RETURN Returns the unsigned long number.
 * @note \n
 */
unsigned long mx_hex_to_nbr(const char *hex);

/**
 * @NAME Integer to ASCII
 * @DESCRIPTION Create a function that takes an integer
 * and converts it to a string.
 * @RETURN Returns the number as a NULL-terminated string.
 * @note \n
 */
char *mx_itoa(int number);

/**
 * @NAME For each
 * @DESCRIPTION Create a function that applies the function f
 * for each element of the array arr given size.
 * @note \n
 */
void mx_foreach(int *arr, int size, void (*f)(int));

/**
 * @NAME Binary search
 * @DESCRIPTION Create a function that: \n
 * - searches the string s in the array arr
 * with the given size of array \n
 * - uses the binary search algorithm assuming that
 * the input array has already been sorted in a lexicographical order
 * @RETURN - returns the index of the found string in the array \n
 * - returns -1 in case of errors
 * or if the string has not been found \n
 * - assigns the number of required iterations to the count pointer
 * @note \n
 */
int mx_binary_search(char **arr, int size, const char *s, int *count);

/**
 * @NAME Bubble sort
 * @DESCRIPTION Create a function that: \n
 * - sorts an array of strings in place in lexicographical order \n
 * - uses the bubble sort algorithm
 * @RETURN - Returns the number of swap operations.
 * @note \n
 */
int mx_bubble_sort(char **arr, int size);

int mx_quicksort(char **arr, int left, int right);

// String pack
// ==================================================================

/**
 * @NAME String length
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strlen.
 * @note \n
 */
int mx_strlen(const char *s);

/**
 * @NAME Swap characters
 * @DESCRIPTION Create a function that swaps the characters
 * of a string using pointers. Do nothing if s1 or s2 does not exist.
 * @note \n
 */
void mx_swap_char(char *s1, char *s2);

/**
 * @NAME Reverse string
 * @DESCRIPTION Create a function that  reverses a string using pointers.
 * Do nothing if a string does not exist.
 * @note \n
 */
void mx_str_reverse(char *s);

/**
 * @NAME Delete string
 * @DESCRIPTION Create a function that: \n
 * takes a pointer to a string \n
 * fries string memory with free \n
 * sets the string to NULL
 * @note \n
 */
void mx_strdel(char **str);

/**
 * @NAME Delete array of strings
 * @DESCRIPTION Create a function that:\n
 *  takes a pointer to a NULL-terminated array of strings \n
 *  deletes the contents of the array \n
 *  frees array memory with free \n
 *  sets a pointer to NULL
 * @note \n
 */
void mx_del_strarr(char ***arr);

/**
 * @NAME Get character index
 * @DESCRIPTION Create a function that finds the index of the first occurrence
 * of the character c in a string str.
 * A string is a sequence of characters, excluding NULL in the end.
 * @RETURN returns the index of the first occurrence \n
 * returns -1 if no occurrence is found \n
 * returns -2 if the string does not exist
 * @note \n
 */
int mx_get_char_index(const char *str, char c);

/**
 * @NAME Duplicate string
 * @DESCRIPTION Create a function that has the same behavior
 *  as the standard libc function strdup.
 * @note \n
 */
char *mx_strdup(const char *s1);

/**
 * @NAME Duplicate part of string
 * @DESCRIPTION Create a function that has the same behavior
 *  as the standard libc function strndup.
 * @note \n
 */
char *mx_strndup(const char *s1, size_t n);

/**
 * @NAME Copy string
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strcpy.
 * @note \n
 */
char *mx_strcpy(char *dst, const char *src);

/**
 * @NAME Copy them all
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strncpy.
 * @note \n
 */
char *mx_strncpy(char *dst, const char *src, int len);

/**
 * @NAME Compare strings
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strcmp.
 * @note \n
 */
int mx_strcmp(const char *s1, const char *s2);

/**
 * @NAME Concatenate strings
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strcat.
 * @note \n
 */
char *mx_strcat(char *restrict s1, const char *restrict s2);

/**
 * @NAME Locate a substring
 * @DESCRIPTION Create a function that has the same behavior
 *  as the standard libc function strstr.
 * @note \n
 */
char *mx_strstr(const char *haystack, const char *needle);

/**
 * @NAME Additional
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function strncmp.
 * @note \n
 */
int mx_strncmp(const char *s1, const char *s2, int n);

/**
 * @NAME Get substring index
 * @DESCRIPTION Create a function that finds the index of a substring.
 * @RETURN returns the index of the first character of sub in str \n
 * returns -1 if sub is not found in str\n
 * returns -2 if str or sub does not exist
 * @note \n
 */
int mx_get_substr_index(const char *str, const char *sub);

/**
 * @NAME Count substrings
 * @DESCRIPTION Create a function that
 * counts the substrings sub in the string str.
 * @RETURN returns the count of sub in str. \n
 * returns 0 if sub is an empty string
 * @note \n
 */
int mx_count_substr(const char *str, const char *sub);

/**
 * @NAME Count words
 * @DESCRIPTION Create a function that counts words in a string. \n
 *  Word is a sequence of characters separated by a delimiter.
 *  @RETURN Returns the number of words in the string.
 * @note \n
 */
int mx_count_words(const char *str, char c);

/**
 * @NAME New string
 * @DESCRIPTION Create a function that:\n
 * allocates memory for a string of a specific size and one additional byte
 * for the terminating '\0'\n
 * initializes each character with '\0'
 * @RETURN returns the string of a specific\n
 * returns NULL if creation fails
 * @note \n
 */
char *mx_strnew(const int size);

/**
 * @NAME Trim string
 * @DESCRIPTION Create a function that: \n
 * takes a string, and creates a new one from it
 * without whitespace characters at the beginning and the end of the string; \n
 * frees all unused memory
 * @RETURN returns a new trimmed string; \n
 * returns NULL if the string str does not exist or string trim fails
 * @note \n
 */
char *mx_strtrim(const char *str);

/**
 * @NAME Clean string
 * @DESCRIPTION Create a function that: \n
 * Takes a string and creates a new one from it without whitespace characters
at the beginning
 * and/or at the end of the string. \n
 * Separates words in the new string with exactly one space character. \n
 * Frees all unused memory.
 * @RETURN returns a new created string; \n
 * returns NULL if the string str does not exist or string creation fails
 * @note \n
 */
char *mx_del_extra_spaces(const char *str);

/**
 * @NAME Split string
 * @DESCRIPTION Create a function that:\n
 * converts a string s to a NULL-terminated array of words \n
 * frees all unused memory \n
 * A word is a sequence of characters separated by the character c as a delimiter.
 * @RETURN returns the NULL-terminated array of strings \n
 * returns NULL if the string s does not exist or creation fails
 * @note \n
 */
char **mx_strsplit(const char *s, char c);

/**
 * @NAME Join strings
 * @DESCRIPTION Create a function that:\n
 *  concatenates strings s1 and s2 into a new string \n
 *  terminates the new string with '\0'
 *  @RETURN returns the string as a result of concatenation s1 and s2 \n
 *  returns the new copy of non-NULL parameter
 *  if one and only one of the parameters is NULL \n
 *  returns NULL if the concatenation fails
 * @note \n
 */
char *mx_strjoin(const char *s1, const char *s2);

/**
 * @NAME File to string
 * @DESCRIPTION Create a function that: \n
 * takes a filename as a parameter \n
 * reads data fom the file into a sting
 * @RETURN returns a NULL-terminated string \n
 * returns NULL in case of any errors
 * @note DO NOT USE THIS FUNCTION IT CONTAINS BUGS \n
 */
char *mx_file_to_str(const char *file);

/**
 * @NAME Replace substrings
 * @DESCRIPTION Create a function that replaces all occurrences
 * of sub in str with replace
 * @RETURN returns a new string where substrings are replaced \n
 * returns NULL  if sub or str or replace does not exist
 * @note \n
 */
char *mx_replace_substr(const char *str, const char *sub, const char *replace);

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

// ==================================================================

void *mx_memset(void *b, int c, size_t len);

/**
 * @NAME Copy memory
 * @DESCRIPTION Create a function that  has the same behavior
 * as the standard libc function memcpy. \n
 * @note \n
 */
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);

/**
 * @NAME Copy memory to ...
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memccpy.\n
 * @note \n
 */
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);

/**
 * @NAME Compare memory
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memcmp. \n
 * @note \n
 */
int mx_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @NAME Locate byte from start
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard stdlib function memchr. \n
 * @note \n
 */

void *mx_memchr(const void *s, int c, size_t n);

/**
 * @NAME Locate byte from end
 * @DESCRIPTION Create a function mx_memrchr,
 * which is similar to the function mx_memchr,
 * except that it searches in the opposite direction
 * from the end of the bytes n points to s
 * instead of directly from the beginning.\n
 * @note \n
 */
void *mx_memrchr(const void *s, int c, size_t n);

/**
 * @NAME Locate block of bytes
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memmem.\n
 * @note \n
 */
void *mx_memmem(const void *big, size_t big_len,
                const void *little, size_t little_len);

/**
 * @NAME Non-overlapping memory copy
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memmove.\n
 * @note \n
 */
void *mx_memmove(void *dst, void *src, size_t len);

/**
 * @NAME Reallocate memory
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function realloc.\n
 * @note \n
 */
void *mx_realloc(void *ptr, size_t size);

// ==================================================================

/**
 * @NAME Create node
 * @DESCRIPTION Create a function that
 * creates a new node of a linked list t_list.
 * The function assigns a parameter data to the list variable data
 * and assigns next to NULL.\n
 * @note \n
 */
t_list *mx_create_node(void *data);

/**
 * @NAME Push front
 * @DESCRIPTION Create a function that inserts a new node of t_list type
 * with the given parameter data at the beginning of the linked list. /n
 * @note \n
 */
void mx_push_front(t_list **list, void *data);

/**
 * @NAME Push back
 * @DESCRIPTION Create a function that inserts a node of t_list type
 * with the given parameter data at the end of the linked list. /n
 * @note \n
 */
void mx_push_back(t_list **list, void *data);

/**
 * @NAME Pop front
 * @DESCRIPTION Create a function that removes the first node of the linked list
 * and frees the memory allocated for the node.
 * @note \n
 */
void mx_pop_front(t_list **head);

/**
 * @NAME Pop back
 * @DESCRIPTION Create a function that removes the last node
 * of the linked list and frees the memory allocated for the node.
 * @note \n
 */
void mx_pop_back(t_list **head);

/**
 * @NAME Size of list
 * @DESCRIPTION Create a function
 * that calculates the number of nodes in a linked list.
 * @RETURN Returns the amount of nodes in the linked list.
 * @note \n
 */
int mx_list_size(t_list *list);

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
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));

#endif // LIBMX_H
