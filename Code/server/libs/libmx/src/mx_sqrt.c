#include "libmx.h"

/**
* @NAME Square root
* @DESCRIPTION Create a function that computes
 * the non-negative square root of "x". \n
* The function must compute square root in less than 2 seconds.
* @RETURN Returns the square root of the number "x"
* if it is natural, and 0 otherwise.
* @note \n
*/

int mx_sqrt(int x) {
    if (x < 0) return 0;
    int left = 0;
    int right = (x < 46341) ? x : 46340;
	// 46341^2 > INT_MAX
    int mid;
    int sq;
    while (left <= right) {
        mid = (left + right) / 2;
        sq = mid * mid;
        if (sq == x) return mid;
        else if (sq < x) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}
