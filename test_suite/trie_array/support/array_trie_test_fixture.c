#include "trie_test_fixture.h"

const noizu_trie_a __internal_array_test_trie_arr[] = {
	{0, 0, 0, 0},
	{'*', 0, 2, 0},
	{'c', 3, 102, 0},
	{'d', 4, 10, 0},
	{'e', 5, 33, 0},
	{'f', 6, 50, 0},
	{'h', 7, 62, 0},
	{'o', 8, 72, 0},
	{'r', 9, 80, 0},
	{'t', 0, 96, 0},
	{'e', 0, 11, 0},
	{'g', 0, 12, 0},
	{'r', 0, 13, 0},
	{'e', 0, 14, 0},
	{'e', 0, 15, 0},
	{'s', 0, 16, 0},
	{'_', 0, 17, 0},
	{'c', 0, 18, 0},
	{'e', 0, 19, 0},
	{'l', 0, 20, 0},
	{'s', 0, 21, 0},
	{'i', 0, 22, 0},
	{'u', 0, 23, 0},
	{'s', 0, 24, ARRAY_JV_DEGREES_CELSIUS},
	{'_', 0, 25, 0},
	{'c', 0, 26, 0},
	{'o', 0, 27, 0},
	{'n', 0, 28, 0},
	{'t', 0, 29, 0},
	{'e', 0, 30, 0},
	{'n', 0, 31, 0},
	{'t', 0, 32, 0},
	{'s', 0, 0, ARRAY_JV_DEGREES_CELSIUS_CONTENTS},
	{'n', 34, 45, 0},
	{'s', 0, 35, 0},
	{'c', 0, 36, 0},
	{'a', 0, 37, 0},
	{'p', 0, 38, 0},
	{'e', 0, 39, 0},
	{'d', 0, 40, 0},
	{'"', 0, 41, 0},
	{'c', 0, 42, 0},
	{'h', 0, 43, 0},
	{'a', 0, 44, 0},
	{'r', 0, 0, ARRAY_JV_ESCAPE},
	{'a', 0, 46, 0},
	{'b', 0, 47, 0},
	{'l', 0, 48, 0},
	{'e', 0, 49, 0},
	{'d', 0, 0, ARRAY_JK_ENABLED},
	{'e', 51, 56, 0},
	{'i', 0, 52, 0},
	{'e', 0, 53, 0},
	{'l', 0, 54, 0},
	{'d', 0, 55, 0},
	{'s', 0, 0, ARRAY_JK_FIELDS},
	{'a', 0, 57, 0},
	{'t', 0, 58, 0},
	{'u', 0, 59, 0},
	{'r', 0, 60, 0},
	{'e', 0, 61, 0},
	{'d', 0, 0, ARRAY_JK_FEATURED},
	{'e', 0, 63, 0},
	{'l', 0, 64, 0},
	{'l', 0, 65, 0},
	{'o', 0, 66, ARRAY_HELLO},
	{'+', 0, 67, 0},
	{'h', 0, 68, 0},
	{'e', 0, 69, 0},
	{'l', 0, 70, 0},
	{'l', 0, 71, 0},
	{'o', 0, 0, ARRAY_HELLO_HELLO},
	{'n', 73, 79, 0},
	{'p', 0, 74, 0},
	{'t', 0, 75, 0},
	{'i', 0, 76, 0},
	{'o', 0, 77, 0},
	{'n', 0, 78, 0},
	{'s', 0, 0, ARRAY_JK_OPTIONS},
	{'e', 0, 0, ARRAY_JK_ONE},
	{'e', 0, 81, 0},
	{'l', 0, 82, 0},
	{'a', 0, 83, 0},
	{'t', 0, 84, 0},
	{'i', 0, 85, 0},
	{'v', 0, 86, 0},
	{'e', 0, 87, 0},
	{'_', 0, 88, 0},
	{'h', 0, 89, 0},
	{'u', 0, 90, 0},
	{'m', 0, 91, 0},
	{'i', 0, 92, 0},
	{'d', 0, 93, 0},
	{'i', 0, 94, 0},
	{'t', 0, 95, 0},
	{'y', 0, 0, ARRAY_JV_RELATIVE_HUMIDITY},
	{'h', 97, 99, 0},
	{'w', 0, 98, 0},
	{'o', 0, 0, ARRAY_JK_TWO},
	{'r', 0, 100, 0},
	{'e', 0, 101, 0},
	{'e', 0, 0, ARRAY_JK_THREE},
	{'o', 0, 103, 0},
	{'n', 0, 104, 0},
	{'t', 0, 105, 0},
	{'e', 0, 106, 0},
	{'n', 0, 107, 0},
	{'t', 0, 108, 0},
	{'s', 0, 0, ARRAY_JK_CONTENTS}
};



struct noizu_trie__array__definition __internal_array_test_trie_inner_def = {
	.trie = __internal_array_test_trie_arr,
	.trie_length = 109,
};



struct noizu_trie_definition array_test_trie = {
	.constant = 1,
	.type = TRIE_ARRAY_TYPE,
	.type_definition = &__internal_array_test_trie_inner_def,
	.trie_init = noizu_trie__array__init,
	.trie_reset = noizu_trie__array__reset,
	.trie_free = noizu_trie__array__free,
	.trie_validate = noizu_trie__array__validate,
	.trie_advance = noizu_trie__array__advance,
	.trie_tokenize = NULL
};

