// Rhyker Mohr
// CSCI 112 Fall 2026
// Programming Assignment #10
// I declare that I am the author of this work, take full responsibility for it, and have disclosed any material external assistance.
#ifndef CODE_H
#define CODE_H

/*
 * CSCI 112 Assignment 10 - Comparators, Generic Bubble Sort and qsort()
 *
 * This header is complete: it contains the types and the prototypes of all
 * 21 functions. Do NOT change any signature - the automated tests rely on
 * them. You implement the functions in code.c.
 *
 * Each prototype is preceded by a short description of what the function
 * must do. The detailed step-by-step notes are in code.c.
 */

#include <stdbool.h>
#include <stddef.h>

#define NAME_LEN 16     /* size of a name buffer, including the '\0' */

/*
 * A comparator has exactly the shape that qsort() expects. It receives
 * POINTERS TO TWO ELEMENTS of the array and returns:
 *   a negative number  if *a should come BEFORE *b,
 *   zero               if they are equal,
 *   a positive number  if *a should come AFTER  *b.
 */
typedef int (*Comparator)(const void *a, const void *b);

typedef struct
{
    char name[NAME_LEN];
    int age;
    float score;
} Student;

/* ======================================================================
 * PART 1: Comparators
 * ====================================================================== */

/*
 * STEP 1: compare_int_asc
 * Comparator for an array of int, ascending order (smaller first).
 * Must be correct for ALL ints, including INT_MIN and INT_MAX.
 */
int compare_int_asc(const void *a, const void *b);

/*
 * STEP 2: compare_int_desc
 * Comparator for an array of int, descending order (larger first).
 */
int compare_int_desc(const void *a, const void *b);

/*
 * STEP 3: compare_float_asc
 * Comparator for an array of float, ascending order. Must distinguish
 * values that differ by less than 1 (for example 1.5 and 1.2).
 */
int compare_float_asc(const void *a, const void *b);

/*
 * STEP 4: compare_float_desc
 * Comparator for an array of float, descending order.
 */
int compare_float_desc(const void *a, const void *b);

/*
 * STEP 5: compare_str_asc
 * Comparator for an array of FIXED-SIZE strings (char names[N][LEN]).
 * Each element IS the string, so the pointer you receive points to its
 * first character. Compares the whole strings, ascending (dictionary order
 * by character codes, so "Zebra" comes before "apple").
 */
int compare_str_asc(const void *a, const void *b);

/*
 * STEP 6: compare_str_desc
 * The same as compare_str_asc, but descending.
 */
int compare_str_desc(const void *a, const void *b);

/*
 * STEP 7: compare_strptr_asc
 * Comparator for an array of POINTERS to strings (char *strs[N]). Here each
 * element is a char *, so the pointers you receive point to a char * (they
 * are char **). Compares the pointed-to strings, ascending.
 */
int compare_strptr_asc(const void *a, const void *b);

/*
 * STEP 8: compare_strptr_desc
 * The same as compare_strptr_asc, but descending.
 */
int compare_strptr_desc(const void *a, const void *b);

/* ======================================================================
 * PART 2: Your own generic sort
 * ====================================================================== */

/*
 * STEP 9: swap_elements
 * Exchanges the contents of two memory blocks of `size` bytes, byte by byte
 * (no malloc, no helper array). Does nothing if a or b is NULL, if both
 * point to the same block, or if size is 0.
 */
void swap_elements(void *a, void *b, size_t size);

/*
 * STEP 10: bubble_sort
 * A generic bubble sort with the same parameters as qsort(): the array
 * `base` of `count` elements of `size` bytes each, ordered by `compare`.
 * It must work for any element type. It sorts in place and is stable
 * (equal elements keep their order). Pass number k (k = 0, 1, ...) compares
 * only the first count-1-k pairs, and the sort stops after a pass in which
 * nothing was swapped. Does nothing if base or compare is NULL, size is 0
 * or count < 2.
 */
void bubble_sort(void *base, size_t count, size_t size, Comparator compare);

/*
 * STEP 11: is_sorted_array
 * Returns true if no element is "greater" than the one after it, that is
 * compare(element i, element i+1) <= 0 for every neighbouring pair.
 * An array with fewer than 2 elements is sorted. Returns false if compare is
 * NULL or size is 0, or if base is NULL while count >= 2.
 */
bool is_sorted_array(const void *base, size_t count, size_t size, Comparator compare);

/* ======================================================================
 * PART 3: Using qsort() and the comparators
 * ====================================================================== */

/*
 * STEP 12: sort_ints
 * Sorts an array of int with the built-in qsort(), ascending or descending.
 * Does nothing if arr is NULL or count < 2.
 */
void sort_ints(int *arr, size_t count, bool ascending);

/*
 * STEP 13: sort_floats
 * Sorts an array of float with qsort(), ascending or descending.
 * Does nothing if arr is NULL or count < 2.
 */
void sort_floats(float *arr, size_t count, bool ascending);

/*
 * STEP 14: sort_names
 * Sorts an array of fixed-size names (each NAME_LEN bytes) with qsort(),
 * ascending or descending. Think about what the element size is.
 * Does nothing if names is NULL or count < 2.
 */
void sort_names(char names[][NAME_LEN], size_t count, bool ascending);

/*
 * STEP 15: sort_string_pointers
 * Sorts an array of char * with qsort(), ascending or descending. Only the
 * pointers move; the strings they point to are not changed.
 * Does nothing if strs is NULL or count < 2.
 */
void sort_string_pointers(char **strs, size_t count, bool ascending);

/*
 * STEP 16: sorted_copy
 * Returns a NEW heap block with the elements of arr sorted ascending. The
 * original array is not modified. The caller owns (and must free) the
 * result. Returns NULL if arr is NULL, count is 0 or the allocation fails.
 */
int *sorted_copy(const int *arr, size_t count);

/*
 * STEP 17: find_median
 * Stores the median of the values in *out and returns true. With an odd
 * count the median is the middle value of the sorted data; with an even
 * count it is the average of the two middle values. The array is not
 * modified and no memory may leak. Returns false (and leaves *out alone)
 * if arr is NULL, count is 0, out is NULL or an allocation fails.
 */
bool find_median(const int *arr, size_t count, float *out);

/*
 * STEP 18: has_duplicates
 * Returns true if some value occurs at least twice. The array is not
 * modified and no memory may leak. Returns false if arr is NULL or
 * count < 2 (or if an allocation fails).
 */
bool has_duplicates(const int *arr, size_t count);

/*
 * STEP 19: compare_students_by_age
 * Comparator for an array of Student: younger students first. Students
 * with the same age compare as equal.
 */
int compare_students_by_age(const void *a, const void *b);

/*
 * STEP 20: compare_students_ranking
 * Comparator for an array of Student that builds a ranking: HIGHER score
 * first; students with the same score are ordered by name, ascending.
 * Students with the same score and name compare as equal.
 */
int compare_students_ranking(const void *a, const void *b);

/*
 * STEP 21: rank_students
 * Sorts an array of Student into the ranking order defined by
 * compare_students_ranking, using qsort().
 * Does nothing if students is NULL or count < 2.
 */
void rank_students(Student *students, size_t count);

#endif
