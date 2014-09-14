#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
/* LICENSE: it is too simple for being licensed.
 * Any code which looks like this will be considered as accidential */

/*
	BSEARCH_STRUCT(long) bs;
	BSEARCH_INIT_SEARCH_LAST(&bs, count);
	while (BSEARCH_LAST_NOT_FOUND(&bs)) {
		BSEARCH_STEP_TO_LAST_LE(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of last less or equal %d equal %d", bs.mid, bs.equal);

	BSEARCH_INIT_SEARCH_FIRST(&bs, count);
	while (BSEARCH_FIRST_NOT_FOUND(&bs)) {
		BSEARCH_STEP_TO_FIRST_GT(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of first greater %d", bs.mid);

	BSEARCH_INIT_SEARCH_EQUAL(&bs, count);
	while (BSEARCH_EQUAL_NOT_FOUND(&bs)) {
		BSEARCH_STEP_TO_EQUAL(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of some equal or first greater %d equal %d", bs.mid, bs.equal);
*/
#define BSEARCH_STRUCT(index_t) struct { index_t low, high, mid; int equal; }
#define BSEARCH_STRUCT_NAME(index_t, name) struct name { index_t low, high, mid; int equal; }

#define BSEARCH_INIT_SEARCH_LAST(bs_, count) do { \
	__typeof__(bs_) _bs_ = (bs_); _bs_->low = _bs_->mid = -1; _bs_->high = (count) - 1; _bs_->equal = 0; \
	assert(_bs_->low <= _bs_->high); \
} while(0)

#define BSEARCH_LAST_NOT_FOUND(bs_) ({ \
	__typeof__(bs_) _bs_ = (bs_); \
	_bs_->mid = _bs_->low + ((_bs_->high - _bs_->low + 1) / 2); \
	_bs_->low < _bs_->high; \
})

#define BSEARCH_STEP_TO_LAST_LE(bs_, cmp_) do { \
	__typeof__(bs_) _bs_ = (bs_); \
	__typeof__(cmp_) _cmp_ = (cmp_); \
	if (_cmp_ >= 0) { _bs_->low = _bs_->mid; _bs_->equal = _cmp_ == 0; } \
	else { _bs_->high = _bs_->mid - 1; } \
} while(0)

#define BSEARCH_STEP_TO_LAST_LT(bs_, cmp_) do { \
	__typeof__(bs_) _bs_ = (bs_); \
	__typeof__(cmp_) _cmp_ = (cmp_); \
	if (_cmp_ > 0) { _bs_->low = _bs_->mid; } \
	else { _bs_->high = _bs_->mid - 1; } \
} while(0)

#define BSEARCH_INIT_SEARCH_FIRST(bs_, count) do { \
	__typeof__(bs_) _bs_ = (bs_); _bs_->low = _bs_->mid = 0; _bs_->high = (count); _bs_->equal = 0; \
	assert(_bs_->low <= _bs_->high); \
} while(0)

#define BSEARCH_FIRST_NOT_FOUND(bs_) ({ \
	__typeof__(bs_) _bs_ = (bs_); \
	_bs_->mid = _bs_->low + ((_bs_->high - _bs_->low) / 2); \
	_bs_->low < _bs_->high; \
})

#define BSEARCH_STEP_TO_FIRST_GE(bs_, cmp_) do { \
	__typeof__(bs_) _bs_ = (bs_); \
	__typeof__(cmp_) _cmp_ = (cmp_); \
	if (_cmp_ <= 0) { _bs_->high = _bs_->mid; _bs_->equal = _cmp_ == 0; } \
	else { _bs_->low = _bs_->mid + 1; } \
} while(0)

#define BSEARCH_STEP_TO_FIRST_GT(bs_, cmp_) do { \
	__typeof__(bs_) _bs_ = (bs_); \
	__typeof__(cmp_) _cmp_ = (cmp_); \
	if (_cmp_ < 0) { _bs_->high = _bs_->mid; } \
	else { _bs_->low = _bs_->mid + 1; } \
} while(0)

#define BSEARCH_INIT_SEARCH_EQUAL(bs_, count) BSEARCH_INIT_SEARCH_FIRST((bs_), (count))
#define BSEARCH_EQUAL_NOT_FOUND(bs_) BSEARCH_FIRST_NOT_FOUND(bs_)
#define BSEARCH_STEP_TO_EQUAL(bs_, cmp_) do { \
	__typeof__(bs_) _bs_ = (bs_); \
	__typeof__(cmp_) _cmp_ = (cmp_); \
	if (_cmp_ < 0) { _bs_->high = _bs_->mid; } \
	else if (_cmp_ > 0) { _bs_->low = _bs_->mid + 1; } \
	else { _bs_->low = _bs_->high = _bs_->mid; _bs_->equal = 1; } \
} while(0)

/*
	// if int indices are just enough
	bs_t bs;
	bs_init_search_last(&bs, count);
	while (bs_last_not_found(&bs)) {
		bs_step_to_last_le(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of last less or equal %d equal %d", bs.mid, bs.equal);

	bs_init_search_first(&bs, count);
	while (bs_first_not_found(&bs)) {
		bs_step_to_first_gt(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of first greater %d", bs.mid);

	bs_init_search_equal(&bs, count);
	while (bs_equal_not_found(&bs)) {
		bs_step_to_equal(&bs, cmp(key, objs[bs.mid]));
	}
	print("index of some equal or first greater %d equal %d", bs.mid, bs.equal);
*/
typedef BSEARCH_STRUCT(int) bs_t;
static inline void bs_init_search_last(bs_t *bs, int count) { BSEARCH_INIT_SEARCH_LAST(bs, count); }
static inline void bs_init_search_first(bs_t *bs, int count) { BSEARCH_INIT_SEARCH_FIRST(bs, count); }
static inline void bs_init_search_equal(bs_t *bs, int count) { BSEARCH_INIT_SEARCH_EQUAL(bs, count); }
static inline int  bs_last_not_found(bs_t *bs) { return BSEARCH_LAST_NOT_FOUND(bs); }
static inline int  bs_first_not_found(bs_t *bs) { return BSEARCH_FIRST_NOT_FOUND(bs); }
static inline int  bs_equal_not_found(bs_t *bs) { return BSEARCH_EQUAL_NOT_FOUND(bs); }
static inline void bs_step_to_last_le(bs_t *bs, int64_t cmp) { BSEARCH_STEP_TO_LAST_LE(bs, cmp); }
static inline void bs_step_to_last_lt(bs_t *bs, int64_t cmp) { BSEARCH_STEP_TO_LAST_LT(bs, cmp); }
static inline void bs_step_to_first_ge(bs_t *bs, int64_t cmp) { BSEARCH_STEP_TO_FIRST_GE(bs, cmp); }
static inline void bs_step_to_first_gt(bs_t *bs, int64_t cmp) { BSEARCH_STEP_TO_FIRST_GT(bs, cmp); }
static inline void bs_step_to_equal(bs_t *bs, int64_t cmp) { BSEARCH_STEP_TO_EQUAL(bs, cmp); }

#endif
