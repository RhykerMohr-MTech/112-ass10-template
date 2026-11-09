// Rhyker Mohr
// CSCI 112 Fall 2026
// Programming Assignment #10
// I declare that I am the author of this work, take full responsibility for it, and have disclosed any material external assistance.

#include <stdlib.h>
#include <string.h>
#include "code.h"

/*
 * Every function below is a skeleton that already compiles. Replace the
 * "// TODO" line (and the "(void)..." lines under it, which only silence
 * "unused parameter" warnings) with your implementation.
 *
 * RULES (they apply to every function):
 *  - Only the standard library: <stdlib.h>, <string.h>, <stdbool.h>, <stddef.h>.
 *  - NULL arguments must never crash your function (see each description).
 *  - Every block you allocate must be freed - no leaks.
 *  - Compile with:  gcc -std=c99 -g -Wall -Wextra -fsanitize=address,undefined main.c code.c -o main
 *
 * REMEMBER: a comparator receives POINTERS TO ELEMENTS (const void *).
 * Cast the pointer to "pointer to the element type" first, then dereference:
 *      int x = *(const int *)a;
 */

/* ======================================================================
 * PART 1: Comparators
 * ====================================================================== */

/*
 * STEP 1: compare_int_asc
 *
 * Return a negative number if *a < *b, 0 if they are equal, a positive
 * number if *a > *b.
 *  - Do NOT return x - y: for INT_MAX and -1 the subtraction overflows.
 *  - Safe idiom:  return (x > y) - (x < y);   (a comparison gives 0 or 1)
 */

int compare_int_asc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/*
 * STEP 2: compare_int_desc
 *
 * The same as compare_int_asc, but larger numbers come first.
 *  - Hint: you do not need to write the comparison again. What happens if you
 *    call compare_int_asc with the two arguments swapped?
 */

int compare_int_desc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 3: compare_float_asc
 *
 * Same contract, for floats.
 *  - Do NOT return (int)(x - y): the difference 1.5 - 1.2 = 0.3 becomes 0
 *    and the two values would look equal.
 *  - The same (x > y) - (x < y) idiom works for floats.
 */

int compare_float_asc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 4: compare_float_desc
 *
 * The same as compare_float_asc, but larger numbers come first.
 */

int compare_float_desc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 5: compare_str_asc
 *
 * For an array like  char names[N][LEN]. Each ELEMENT is a whole string, so
 * the pointer you receive already points to the first character of the string
 * (cast it to const char *). Compare the whole strings with strcmp().
 *  - Order is by character codes: "Zebra" comes before "apple".
 */

int compare_str_asc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 6: compare_str_desc
 *
 * The same as compare_str_asc, but reversed (swap the arguments).
 */

int compare_str_desc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 7: compare_strptr_asc
 *
 * For an array like  char *strs[N]. Now each ELEMENT is a char *, so the
 * pointer you receive points to a char * (it is really a char **).
 * First get the string pointer out of the element:
 *      const char *x = *(const char * const *)a;
 * then compare the strings with strcmp().
 *  - This is the most common qsort() mistake: compare_str_asc and
 *    compare_strptr_asc are NOT interchangeable.
 */

int compare_strptr_asc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 8: compare_strptr_desc
 *
 * The same as compare_strptr_asc, but reversed.
 */

int compare_strptr_desc(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/* ======================================================================
 * PART 2: Your own generic sort
 * ====================================================================== */

/*
 * STEP 9: swap_elements
 *
 * Exchange two blocks of `size` bytes.
 *  - Do nothing if a or b is NULL, if a == b, or if size == 0.
 *  - A void * cannot be indexed or incremented. Cast both pointers to
 *    unsigned char * and swap the blocks byte by byte in a loop
 *    (one temporary unsigned char is enough, no malloc).
 */

void swap_elements(void *a, void *b, size_t size)
{
    // TODO
    (void)a;
    (void)b;
    (void)size;
}

/*
 * STEP 10: bubble_sort
 *
 * A generic bubble sort with the same parameters as qsort().
 *  - Do nothing if base or compare is NULL, size == 0 or count < 2.
 *  - base is a void *: cast it to unsigned char *. The address of element i
 *    is  (unsigned char *)base + i * size.
 *  - Repeat passes. In pass number k (k = 0, 1, 2, ...) compare only the
 *    first count - 1 - k pairs of neighbours: the last k elements are already
 *    in place.
 *  - Swap two neighbours (use swap_elements) ONLY when
 *    compare(left, right) > 0. Never swap equal elements - then the sort is
 *    stable (equal elements keep their order).
 *  - Remember whether the pass swapped anything. If it did not, the array is
 *    sorted: stop immediately.
 *  - Expected number of comparisons: an already sorted array needs exactly
 *    count - 1; a reversed array needs count * (count - 1) / 2.
 */

void bubble_sort(void *base, size_t count, size_t size, Comparator compare)
{
    // TODO
    (void)base;
    (void)count;
    (void)size;
    (void)compare;
}

/*
 * STEP 11: is_sorted_array
 *
 * Return true if compare(element i, element i + 1) <= 0 for every pair of
 * neighbours.
 *  - compare == NULL or size == 0 -> false.
 *  - count < 2 -> true.
 *  - base == NULL (with count >= 2) -> false.
 */

bool is_sorted_array(const void *base, size_t count, size_t size, Comparator compare)
{
    // TODO
    (void)base;
    (void)count;
    (void)size;
    (void)compare;
    return false;
}

/* ======================================================================
 * PART 3: Using qsort() and the comparators
 *
 * void qsort(void *base, size_t count, size_t size,
 *            int (*compare)(const void *, const void *));
 *
 * For every function below, decide: what is the base, how many elements are
 * there, how many BYTES is one element, and which comparator fits?
 * ====================================================================== */

/*
 * STEP 12: sort_ints
 *
 * Sort an array of int with qsort(), ascending if `ascending` is true,
 * otherwise descending. Use the comparators from Part 1.
 *  - arr == NULL or count < 2 -> do nothing.
 */

void sort_ints(int *arr, size_t count, bool ascending)
{
    // TODO
    (void)arr;
    (void)count;
    (void)ascending;
}

/*
 * STEP 13: sort_floats
 *
 * The same for an array of float.
 */

void sort_floats(float *arr, size_t count, bool ascending)
{
    // TODO
    (void)arr;
    (void)count;
    (void)ascending;
}

/*
 * STEP 14: sort_names
 *
 * Sort an array of fixed-size names with qsort(). One element is one whole
 * name, so the element size is NAME_LEN bytes (not sizeof(char *) and not
 * strlen). Use compare_str_asc / compare_str_desc.
 *  - names == NULL or count < 2 -> do nothing.
 */

void sort_names(char names[][NAME_LEN], size_t count, bool ascending)
{
    // TODO
    (void)names;
    (void)count;
    (void)ascending;
}

/*
 * STEP 15: sort_string_pointers
 *
 * Sort an array of char * with qsort(). One element is one pointer, so the
 * element size is sizeof(char *). Use compare_strptr_asc / compare_strptr_desc.
 * Only the pointers move; the strings are not touched.
 *  - strs == NULL or count < 2 -> do nothing.
 */

void sort_string_pointers(char **strs, size_t count, bool ascending)
{
    // TODO
    (void)strs;
    (void)count;
    (void)ascending;
}

/*
 * STEP 16: sorted_copy
 *
 * Return a NEW heap block with the elements of arr sorted ascending. The
 * original array must not be modified (that is why you sort a copy).
 *  - malloc (count * sizeof(int)), copy with memcpy, sort the copy with qsort.
 *  - arr == NULL, count == 0 or allocation failure -> return NULL.
 *  - The caller frees the result.
 */

int *sorted_copy(const int *arr, size_t count)
{
    // TODO
    (void)arr;
    (void)count;
    return NULL;
}

/*
 * STEP 17: find_median
 *
 * Store the median in *out and return true.
 *  - Get a sorted copy with sorted_copy() and FREE it before returning.
 *  - Odd count: the middle element, sorted[count / 2].
 *  - Even count: the average of sorted[count / 2 - 1] and sorted[count / 2].
 *    Add them as floats - adding two big ints can overflow int.
 *  - arr == NULL, count == 0, out == NULL or allocation failure -> return
 *    false and do not touch *out.
 */

bool find_median(const int *arr, size_t count, float *out)
{
    // TODO
    (void)arr;
    (void)count;
    (void)out;
    return false;
}

/*
 * STEP 18: has_duplicates
 *
 * Return true if some value occurs at least twice.
 *  - Idea: in a SORTED array equal values stand next to each other. Use
 *    sorted_copy(), look for two equal neighbours, and FREE the copy.
 *  - arr == NULL or count < 2 -> false (also false if the allocation fails).
 */

bool has_duplicates(const int *arr, size_t count)
{
    // TODO
    (void)arr;
    (void)count;
    return false;
}

/*
 * STEP 19: compare_students_by_age
 *
 * Comparator for an array of Student: younger first. Cast the const void *
 * pointers to const Student * and compare the age fields. Same age -> 0.
 */

int compare_students_by_age(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 20: compare_students_ranking
 *
 * Comparator for an array of Student that builds a ranking:
 *  1. HIGHER score first;
 *  2. if the scores are equal, name ascending (strcmp);
 *  3. same score and same name -> 0.
 *  - Compare floats with < and >, never by casting a difference to int.
 */

int compare_students_ranking(const void *a, const void *b)
{
    // TODO
    (void)a;
    (void)b;
    return 0;
}

/*
 * STEP 21: rank_students
 *
 * Sort an array of Student into the ranking order using qsort() and
 * compare_students_ranking. The element size is sizeof(Student).
 *  - students == NULL or count < 2 -> do nothing.
 */

void rank_students(Student *students, size_t count)
{
    // TODO
    (void)students;
    (void)count;
}
