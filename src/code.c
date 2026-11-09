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
    return compare_int_asc(b, a);
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
    float x = *(const float *)a;
    float y = *(const float *)b;
    
    return (x > y) - (x < y);
}

/*
 * STEP 4: compare_float_desc
 *
 * The same as compare_float_asc, but larger numbers come first.
 */

int compare_float_desc(const void *a, const void *b)
{
    float fa = *(const float *)a;
    float fb = *(const float *)b;

    if (fa < fb) return 1;
    if (fa > fb) return -1;
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

    const char *str_a = (const char **)a;
    const char *str_b = (const char **)b;

    return strcmp(str_a, str_b);
}

/*
 * STEP 6: compare_str_desc
 *
 * The same as compare_str_asc, but reversed (swap the arguments).
 */

int compare_str_desc(const void *a, const void *b)
{

    const char *str_a = (const char **)a;
    const char *str_b = (const char **)b;

    return strcmp(str_b, str_a);
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
    const char *str_a = *(const char * const *)a;
    const char *str_b = *(const char * const *)b;
    
    // Compare the strings using strcmp for ascending order
    return strcmp(str_a, str_b);
}

/*
 * STEP 8: compare_strptr_desc
 *
 * The same as compare_strptr_asc, but reversed.
 */

int compare_strptr_desc(const void *a, const void *b)
{
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    
    return strcmp(str_b, str_a);
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
    if (a == NULL || b == NULL || a == b || size == 0) {
        return;
    }

    // Cast pointers to unsigned char * to enable byte-by-byte access
    unsigned char *ptr_a = (unsigned char *)a;
    unsigned char *ptr_b = (unsigned char *)b;

    // Swap the blocks byte by byte using a single temporary variable
    for (size_t i = 0; i < size; i++) {
        unsigned char temp = ptr_a[i];
        ptr_a[i] = ptr_b[i];
        ptr_b[i] = temp;
    }
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
 if (base == NULL || compare == NULL || size == 0 || count < 2) {
        return;
    }

    // Cast base to unsigned char * for byte-accurate pointer arithmetic
    unsigned char *u_base = (unsigned char *)base;

    // Repeat passes
    for (size_t k = 0; k < count - 1; k++) {
        int swapped = 0;

        // Compare only the first count - 1 - k pairs of neighbours
        for (size_t i = 0; i < count - 1 - k; i++) {
            unsigned char *left = u_base + i * size;
            unsigned char *right = u_base + (i + 1) * size;

            // Swap ONLY when compare(left, right) > 0 to maintain stability
            if (compare(left, right) > 0) {
                swap_elements(left, right, size);
                swapped = 1;
            }
        }

        // If the pass did not swap anything, the array is sorted: stop immediately
        if (!swapped) {
            break;
        }
    }
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
if (compare == NULL || size == 0) {
        return false;
    }

    // 2. count < 2 -> true
    if (count < 2) {
        return true;
    }

    // 3. base == NULL (with count >= 2) -> false
    if (base == NULL) {
        return false;
    }

    // Cast to char* to allow byte-level pointer arithmetic
    const char *ptr = (const char *)base;

    // Check if compare(element i, element i + 1) <= 0 for every pair
    for (size_t i = 0; i < count - 1; i++) {
        const void *elem_i = ptr + (i * size);
        const void *elem_next = ptr + ((i + 1) * size);

        if (compare(elem_i, elem_next) > 0) {
            return false; // Array is out of order
        }
    }

    return true;
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
    if (arr == NULL || count < 2) {
        return;
    }

    // Select the appropriate comparator based on the ascending flag
    if (ascending) {
        qsort(arr, count, sizeof(int), compare_int_asc);
    } else {
        qsort(arr, count, sizeof(int), compare_int_desc);
    }
}

/*
 * STEP 13: sort_floats
 *
 * The same for an array of float.
 */

void sort_floats(float *arr, size_t count, bool ascending)
{
if (arr == NULL || count < 2) {
        return;
    }

    if (ascending) {
        qsort(arr, count, sizeof(float), compare_int_asc);
    } else {
        qsort(arr, count, sizeof(float), compare_int_desc);
    }
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
  // 1. Guard clause: do nothing if the array is null or has fewer than 2 elements
    if (names == NULL || count < 2) {
        return;
    }

    // 2. Select the appropriate comparison function based on the boolean flag
    int (*compare_func)(const void *, const void *) = ascending ? compare_str_asc : compare_str_desc;

    // 3. Call qsort with the array, count, the explicit size of one name element, and the function pointer
    qsort(names, count, NAME_LEN, compare_func);
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
// Guard clause: do nothing if array is NULL or has fewer than 2 elements
    if (strs == NULL || count < 2) {
        return;
    }

    // Select the appropriate comparison function based on the boolean flag
    int (*compare_func)(const void *, const void *) = ascending ? compare_strptr_asc : compare_strptr_desc;

    // Execute qsort
    qsort(strs, count, sizeof(char *), compare_func);
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
if (arr == NULL || count == 0) {
        return NULL;
    }
    
    // Allocate a new heap block for the copy
    int *copy = (int *)malloc(count * sizeof(int));
    
    // Check for allocation failure
    if (copy == NULL) {
        return NULL;
    }
    
    // Copy the contents of the original array into the new block
    memcpy(copy, arr, count * sizeof(int));
    
    // Sort the newly created copy in ascending order
    qsort(copy, count, sizeof(int), compare_int_asc);
    
    // Return the sorted copy (caller is responsible for freeing this memory)
    return copy;
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
    // Check for invalid inputs and empty array
    if (arr == NULL || count == 0 || out == NULL) {
        return false;
    }

    // Get a sorted copy of the array
    int *sorted = sorted_copy(arr, count);
    if (sorted == NULL) {
        return false; // Allocation failure
    }

    // Calculate median
    if (count % 2 != 0) {
        // Odd count: middle element
        *out = (float)sorted[count / 2];
    } else {
        // Even count: average of two middle elements
        // Cast to float first to prevent integer overflow when adding
        float left = (float)sorted[count / 2 - 1];
        float right = (float)sorted[count / 2];
        *out = (left + right) / 2.0f;
    }

    // Free the allocated memory before returning true
    free(sorted);
    return true;
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
 // Return false if array pointer is NULL or contains fewer than 2 elements
    if (arr == NULL || count < 2) {
        return false;
    }

    // Create a sorted copy of the array
    int *sorted = sorted_copy(arr, count);
    
    // Return false if the allocation inside sorted_copy failed
    if (sorted == NULL) {
        return false;
    }

    bool duplicate_found = false;

    // Scan for two equal neighbors
    for (size_t i = 0; i < count - 1; i++) {
        if (sorted[i] == sorted[i + 1]) {
            duplicate_found = true;
            break;
        }
    }

    // Always free the dynamically allocated copy before returning
    free(sorted);

    return duplicate_found;
}

/*
 * STEP 19: compare_students_by_age
 *
 * Comparator for an array of Student: younger first. Cast the const void *
 * pointers to const Student * and compare the age fields. Same age -> 0.
 */

int compare_students_by_age(const void *a, const void *b)
{
    // Cast the generic const void * pointers to const Student *
    const Student *student_a = *(const Student **)a;
    const Student *student_b = *(const Student **)b;

    // Compare the age fields: younger first (ascending order)
    if (student_a->age < student_b->age) {
        return -1;
    } else if (student_a->age > student_b->age) {
        return 1;
    }
    
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
    // Cast the generic void pointers to the actual Student struct pointers
    const Student *student_a = (const Student *)a;
    const Student *student_b = (const Student *)b;

    // 1. Higher score first (descending order)
    if (student_a->score > student_b->score) return -1;
    if (student_a->score < student_b->score) return 1;

    // 2. If scores are equal, name ascending (alphabetical order)
    // 3. If names are also equal, strcmp naturally returns 0
    return strcmp(student_a->name, student_b->name);
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
    if (students == NULL || count < 2) {
        return;
    }

    qsort(students, count, sizeof(Student), compare_students_ranking);
}
