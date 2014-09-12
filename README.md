bsearch
=======

Binary search C helper macro and struct

usage
=====

````c
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

	/* if int indices are just enough */
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
````


