#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "bsearch.h"

static int compare_intp(const void *a, const void *b)
{
	return *(int*)a < *(int*)b ? -1 : (*(int*)a > *(int*)b ? 1 : 0);
}

static inline int compare_int(int a, int b)
{
	return a < b ? -1 : (a > b ? 1 : 0);
}
#define N 1023
int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	int *array;
	int i, s;

	srand(1);

	array = malloc(sizeof(array[0]) * N);
	for(i = 0; i < N; i++) {
		array[i] = rand() % N;
	}
	qsort(array, N, sizeof(array[0]), compare_intp);

	for(i = 0; i < N; i++) {
		BSEARCH_STRUCT(int) bs;
		BSEARCH_INIT_SEARCH_LAST(&bs, N);
		s = rand() % N;
		while (BSEARCH_LAST_NOT_FOUND(&bs)) {
			BSEARCH_STEP_TO_LAST_LE(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid >= N) {
			printf("LAST_LE(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid < N-1 && array[bs.mid+1] <= s) {
			printf("LAST_LE(%d) points to %d, and next is %d\n", s, bs.mid, array[bs.mid+1]);
		}
		if (bs.mid > -1 && array[bs.mid] > s) {
			printf("LAST_LE(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		BSEARCH_STRUCT(int) bs;
		BSEARCH_INIT_SEARCH_LAST(&bs, N);
		s = rand() % N;
		while (BSEARCH_LAST_NOT_FOUND(&bs)) {
			BSEARCH_STEP_TO_LAST_LT(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid >= N) {
			printf("LAST_LT(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid < N-1 && array[bs.mid+1] < s) {
			printf("LAST_LT(%d) points to %d, and next is %d\n", s, bs.mid, array[bs.mid+1]);
		}
		if (bs.mid >= 0 && array[bs.mid] >= s) {
			printf("LAST_LT(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		BSEARCH_STRUCT(int) bs;
		BSEARCH_INIT_SEARCH_FIRST(&bs, N);
		s = rand() % N;
		while (BSEARCH_FIRST_NOT_FOUND(&bs)) {
			BSEARCH_STEP_TO_FIRST_GE(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("FIRST_GE(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] >= s) {
			printf("FIRST_GE(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] < s) {
			printf("FIRST_GE(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		BSEARCH_STRUCT(int) bs;
		BSEARCH_INIT_SEARCH_FIRST(&bs, N);
		s = rand() % N;
		while (BSEARCH_FIRST_NOT_FOUND(&bs)) {
			BSEARCH_STEP_TO_FIRST_GT(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("FIRST_GT(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] > s) {
			printf("FIRST_GT(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] <= s) {
			printf("FIRST_GT(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		BSEARCH_STRUCT(int) bs;
		BSEARCH_INIT_SEARCH_EQUAL(&bs, N);
		s = rand() % N;
		while (BSEARCH_EQUAL_NOT_FOUND(&bs)) {
			BSEARCH_STEP_TO_EQUAL(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("EQUAL(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] > s) {
			printf("EQUAL(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] < s) {
			printf("EQUAL(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
		if (bs.mid < N && bs.mid >= 0 && array[bs.mid] == s && !bs.equal) {
			printf("EQUAL(%d) points to %d which is equal, but flag not set\n", s, bs.mid);
		}
	}
	for(i = 0; i < N; i++) {
		bs_t bs;
		bs_init_search_last(&bs, N);
		s = rand() % N;
		while (bs_last_not_found(&bs)) {
			bs_step_to_last_le(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid >= N) {
			printf("last_le(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid < N-1 && array[bs.mid+1] <= s) {
			printf("last_le(%d) points to %d, and next is %d\n", s, bs.mid, array[bs.mid+1]);
		}
		if (bs.mid > -1 && array[bs.mid] > s) {
			printf("last_le(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		bs_t bs;
		bs_init_search_last(&bs, N);
		s = rand() % N;
		while (bs_last_not_found(&bs)) {
			bs_step_to_last_lt(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid >= N) {
			printf("last_lt(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid < N-1 && array[bs.mid+1] < s) {
			printf("last_lt(%d) points to %d, and next is %d\n", s, bs.mid, array[bs.mid+1]);
		}
		if (bs.mid >= 0 && array[bs.mid] >= s) {
			printf("last_lt(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		bs_t bs;
		bs_init_search_first(&bs, N);
		s = rand() % N;
		while (bs_first_not_found(&bs)) {
			bs_step_to_first_ge(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("first_ge(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] >= s) {
			printf("first_ge(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] < s) {
			printf("first_ge(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		bs_t bs;
		bs_init_search_first(&bs, N);
		s = rand() % N;
		while (bs_first_not_found(&bs)) {
			bs_step_to_first_gt(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("FIRST_GT(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] > s) {
			printf("FIRST_GT(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] <= s) {
			printf("FIRST_GT(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
	}
	for(i = 0; i < N; i++) {
		bs_t bs;
		bs_init_search_equal(&bs, N);
		s = rand() % N;
		while (bs_equal_not_found(&bs)) {
			bs_step_to_equal(&bs, compare_int(s, array[bs.mid]));
		}
		if (bs.mid > N || bs.mid < 0) {
			printf("equal(%d) points to %d while size is %d\n", s, bs.mid, N);
		} else if (bs.mid > 0 && array[bs.mid-1] > s) {
			printf("equal(%d) points to %d, and previous is %d\n", s, bs.mid, array[bs.mid-1]);
		}
		if (bs.mid < N && array[bs.mid] < s) {
			printf("equal(%d) points to %d where %d is\n", s, bs.mid, array[bs.mid]);
		}
		if (bs.mid < N && bs.mid >= 0 && array[bs.mid] == s && !bs.equal) {
			printf("equal(%d) points to %d which is equal, but flag not set\n", s, bs.mid);
		}
	}
	printf("BINARY SEARCH TEST DONE\n");
}
