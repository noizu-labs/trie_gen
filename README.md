Noizu Trie Generator
==========================================

The Noizu Trie Generator tool and library may be used to create compile time trie lookup table, with the implementers choice of underlying implementation.

Generate your Trie, copy and paste the generated output into your project and include the noizu_trie.c and noizu_trie.h and implementation specific folders from this projects trie_generator/import directory.

Use in combination with the [Noizu Streaming Json](http://github.com/noizu/streaming-json-parser) for fast compact parsing of too large for memory embedded data streams.

# To Use
Use executable to generate code.
`trie_generator.exe input.txt [output.file|import/generated.gen] [name|trie] [mode|(min|struct)]`

input.txt - file to extract trie from.
output.file - output file for generated trie
name - name of generated trie variable.
mode - array of int or array of struct encoded trie.

Include appropriate noizu_trie_a.h and noizu_trie_a.c or noizu_trie_s.h, noizu_trie_s.c in your applications include path.

# Examples



## Dynamically Sized Bitmap Implementation (Compact)

```c
// compact_test_trie: CharMap
TRIE_CHAR_CODE __internal_compact_test_trie_cm(TRIE_CHAR_CODE c) {
    if (c == '*') return 1;
    if (c == 'c') return 2;
    if (c == 'o') return 3;
    if (c == 'n') return 4;
    if (c == 't') return 5;
    if (c == 'e') return 6;
    if (c == 's') return 7;
    if (c == 'd') return 8;
    if (c == 'g') return 9;
    if (c == 'r') return 10;
    if (c == '_') return 11;
    if (c == 'l') return 12;
    if (c == 'i') return 13;
    if (c == 'u') return 14;
    if (c == 'a') return 15;
    if (c == 'b') return 16;
    if (c == 'f') return 17;
    if (c == 'h') return 18;
    if (c == '+') return 19;
    if (c == 'p') return 20;
    if (c == 'v') return 21;
    if (c == 'm') return 22;
    if (c == 'y') return 23;
    if (c == 'w') return 24;
    return 0;
}

TRIE_CHAR_CODE __internal_compact_test_trie_chars[] = { '*', 'c', 'o', 'n', 't', 'e', 's', 'd', 'g', 'r', '_', 'l', 'i', 'u', 'a', 'b', 'f', 'h', '+', 'p', 'v', 'm', 'y', 'w' };

// compact_test_trie: GetToken
TRIE_TOKEN __internal_compact_test_trie_token(uint32_t index, noizu_trie_definition* definition, uint8_t* has_token) {
    *has_token = 1;
    TRIE_TOKEN token = 0;

    if (index == 8) token = COMPACT_JK_CONTENTS;
    else if (index == 23) token = COMPACT_JV_DEGREES_CELSIUS;
    else if (index == 32) token = COMPACT_JV_DEGREES_CELSIUS_CONTENTS;
    else if (index == 39) token = COMPACT_JK_ENABLED;
    else if (index == 47) token = COMPACT_JK_FEATURED;
    else if (index == 52) token = COMPACT_JK_FIELDS;
    else if (index == 57) token = COMPACT_HELLO;
    else if (index == 63) token = COMPACT_HELLO_HELLO;
    else if (index == 66) token = COMPACT_JK_ONE;
    else if (index == 72) token = COMPACT_JK_OPTIONS;
    else if (index == 89) token = COMPACT_JV_RELATIVE_HUMIDITY;
    else if (index == 94) token = COMPACT_JK_THREE;
    else if (index == 96) token = COMPACT_JK_TWO;
    else *has_token = 0;

    return token;
}



// compact_test_trie: Node Binary| Bits per field = 11, required = 134
unsigned char __internal_compact_test_trie_node_map[] = {
0X08,0X22,0X44,0X60,
0X90,0X12,0X82,0X60,
0X48,0X09,0X41,0X38,
0X08,0XC4,0XC0,0XA4,
0X15,0X02,0X60,0X4C,
0X09,0XC1,0X58,0X22,
0X04,0XC0,0XB0,0X13,
0X82,0XD0,0X5C,0X09,
0XC1,0X58,0X22,0X04,
0X60,0X90,0X12,0X82,
0X60,0X48,0X09,0X41,
0X38,0X06,0X3C,0X80,
0XBC,0X18,0X02,0XC0,
0X4C,0X0A,0000,0X8B,
0X66,0X3D,0XE0,0X94,
0X17,0X02,0XA0,0X4C,
0X0A,0000,0X68,0X26,
0X05,0X80,0XA0,0X13,
0X81,0X25,0XCC,0X0B,
0X01,0X60,0X23,0X06,
0X60,0XC8,0X13,0X02,
0XC0,0X58,0X08,0XC0,
0X1A,0X64,0X14,0XC0,
0X50,0X12,0X82,0XD0,
0X46,0X09,0X01,0X38,
0X0A,0X8C,0XC0,0XB0,
0X17,0X82,0X50,0X5A,
0X0D,0X41,0X30,0X2B,
0X06,0X40,0XB8,0X1B,
0X02,0XD0,0X50,0X0B,
0X41,0X28,0X37,0000,
0XA0,0XC8,0X95,0X02,
0X60,0X4C,0X06,0X01,
0X18,0000, };


// compact_test_trie: Compact Trie Definition, max_sibling_jump=24 rows
struct noizu_trie__compact__definition compact_test_trie_inner_def = {
    .size = 97,
    .tokens = 13,
    .characters = 24,
    .bit_length__character_code = 5,
    .bit_length__sibling_relative_index = 5,
    .bit_length__child_relative_index = 1,
    .bit_length__child_relative_offset = 10,
    .bit_length = 11,
    .trie_raw = __internal_compact_test_trie_node_map,
    .trie_raw_length = 134,
    .char_map = __internal_compact_test_trie_chars,
    .token_code = __internal_compact_test_trie_token,
    .char_code = __internal_compact_test_trie_cm
};
struct noizu_trie_definition compact_test_trie = {
    .constant = 1,
    .type = TRIE_COMPACT_TYPE,
    .type_definition = &compact_test_trie_inner_def,
    .trie_init = noizu_trie__compact__init,
    .trie_free = noizu_trie__compact__free,
    .trie_validate = noizu_trie__compact__validate,
    .trie_advance = noizu_trie__compact__advance,
    .trie_tokenize = NULL
};
```

### Tokenize something
```c

offset_buffer req* = input_source();
struct noizu_trie_options options = {
	 0,
	 .delimiter = '|',
	 .keep_last_token = 1,
	 .hard_delim = 1
};
struct noizu_trie_state state = { 0 };

TRIE_TOKEN outcome = noizu_trie__init(req, &compact_test_trie, options, &state);

if (!(outcome & TRIE_ERROR)) {

   outcome = noizu_trie__tokenize(&state, &compact_test_trie, NULL);
	 if (outcome == TRIE_DELIM_EXIT) {
		 // parse ended on your '|' delimiter not end of buffer or '\0';
	 }


} else {
  /*
// error handling.

	// TRIE RESPONSE CODES - major
	#define TRIE_UNKNOWN 0x0000
	#define TRIE_EXIT 0x1000
	#define TRIE_ERROR 0x2000
	#define TRIE_ARGUMENT_ERROR (TRIE_ERROR | 0x4000)
	#define TRIE_SUCCESS 0x8000

	// TRIE RESPONSE CODES - EXIT
	#define TRIE_RETURN_EXIT (TRIE_EXIT | 0x0200)
	#define TRIE_VALID_EXIT (TRIE_EXIT | TRIE_SUCCESS | 0x0400)
	#define TRIE_ABNORMAL_EXIT (TRIE_EXIT | 0x0800)
	#define TRIE_END_INPUT_EXIT (TRIE_VALID_EXIT | TRIE_RETURN_EXIT |  0x0001)
	#define TRIE_END_PARSE_EXIT (TRIE_VALID_EXIT | TRIE_RETURN_EXIT |  0x0002)
	#define TRIE_CONTINUE (TRIE_VALID_EXIT | 0x0003)
	#define TRIE_DELIM_EXIT (TRIE_VALID_EXIT | TRIE_RETURN_EXIT |  0x0004)
	#define TRIE_OVERFLOW_EXIT (TRIE_ABNORMAL_EXIT | TRIE_RETURN_EXIT | 0x0005)
	#define TRIE_BUFFER_END (TRIE_VALID_EXIT | TRIE_RETURN_EXIT |0x0006)
	#define TRIE_BUFFER_END_ON_SKIP (TRIE_ABNORMAL_EXIT | TRIE_RETURN_EXIT |0x0007)

	// ERRORS
	#define TRIE_ALLOC_FAIL (TRIE_ERROR | 0x0001)
	#define TRIE_DEFINITION_ERROR (TRIE_ERROR | 0x0002)
	#define TRIE_ACCESS_ERROR (TRIE_ERROR | 0x0003)
	#define TRIE_ARRAY_ACCESS_ERROR TRIE_ACCESS_ERROR
	#define TRIE_STRUCT_ACCESS_ERROR TRIE_ACCESS_ERROR

	// Argument Errors
	#define TRIE_ARGUMENT_ERROR__INVALID_TYPE (TRIE_ARGUMENT_ERROR | 0x0100)
	#define TRIE_ARGUMENT_ERROR__INVALID_TYPE_STATE (TRIE_ARGUMENT_ERROR__INVALID_TYPE | 0x0001)
	#define TRIE_ARGUMENT_ERROR__INVALID_TYPE_DEFINITION (TRIE_ARGUMENT_ERROR__INVALID_TYPE | 0x0002)

	#define TRIE_ARGUMENT_ERROR__NULL (TRIE_ARGUMENT_ERROR | 0x0200)
	#define TRIE_ARGUMENT_ERROR__NULL_STATE (TRIE_ARGUMENT_ERROR__NULL | 0x0003)
	#define TRIE_ARGUMENT_ERROR__NULL_DEFINITION (TRIE_ARGUMENT_ERROR__NULL | 0x0004)
	#define TRIE_ARGUMENT_ERROR__NULL_TYPE_STATE (TRIE_ARGUMENT_ERROR__NULL | 0x0005)
	#define TRIE_ARGUMENT_ERROR__NULL_TYPE_DEFINITION (TRIE_ARGUMENT_ERROR__NULL | 0x0006)

	#define TRIE_ARGUMENT_ERROR__TYPE (TRIE_ARGUMENT_ERROR | 0x0400)
	#define TRIE_ARGUMENT_ERROR__TYPE_MISMATCH (TRIE_ARGUMENT_ERROR__TYPE | 0x0007)
	#define TRIE_ARGUMENT_ERROR__TYPE_INIT_NOT_SET (TRIE_ARGUMENT_ERROR__TYPE | 0x0008)
	#define TRIE_ARGUMENT_ERROR__TYPE_VALIDATE_NOT_SET (TRIE_ARGUMENT_ERROR__TYPE | 0x0009)
	#define TRIE_ARGUMENT_ERROR__TYPE_ADVANCE_NOT_SET (TRIE_ARGUMENT_ERROR__TYPE | 0x000A)
	#define TRIE_ARGUMENT_ERROR__TYPE_TOKENIZE_NOT_SET (TRIE_ARGUMENT_ERROR__TYPE | 0x000B)
	#define TRIE_ARGUMENT_ERROR__TYPE_FREE_NOT_SET (TRIE_ARGUMENT_ERROR__TYPE | 0x000C)


	#define TRIE_ERROR_DEALLOC_CONSTANT_DEFINITION (TRIE_ERROR | 0x0010)



	// TRIE SUCCESS
	#define TRIE_INITIALIZED (TRIE_SUCCESS | 0x0001)

	*/

}

    TRIE_TOKEN o = noizu_trie__tokenize(&state, &compact_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, COMPACT_HELLO, 0, 0, '+');
}




```



## Array Implementation

### Generated Source
```c
// Generated Trie
#include "noizu_trie.h"
#include "noizu_trie_a.h"

const noizu_trie_a __internal_array_test_trie_arr[] = {
    {0, 0, 0, 0},
    {'*', 0, 2, 0},
    {'c', 3, 91, 0},
    {'d', 4, 10, 0},
    {'e', 5, 33, 0},
    {'f', 6, 39, 0},
    {'h', 7, 51, 0},
    {'o', 8, 61, 0},
    {'r', 9, 69, 0},
    {'t', 0, 85, 0},
		// .
		// .
		// .
    {'d', 0, 82, 0},
    {'i', 0, 83, 0},
    {'t', 0, 84, 0},
    {'y', 0, 0, ARRAY_JV_RELATIVE_HUMIDITY},
    {'h', 86, 88, 0},
    {'w', 0, 87, 0},
    {'o', 0, 0, ARRAY_JK_TWO},
    {'r', 0, 89, 0},
    {'e', 0, 90, 0},
    {'e', 0, 0, ARRAY_JK_THREE},
    {'o', 0, 92, 0},
    {'n', 0, 93, 0},
    {'t', 0, 94, 0},
    {'e', 0, 95, 0},
    {'n', 0, 96, 0},
    {'t', 0, 97, 0},
    {'s', 0, 0, ARRAY_JK_CONTENTS}
};

struct noizu_trie__array__definition __internal_array_test_trie_inner_def = {
    .trie = (const noizu_trie_a*)__internal_array_test_trie_arr,
    .trie_length = 98,
};

struct noizu_trie_definition array_test_trie = {
    .constant = 1,
    .type = TRIE_ARRAY_TYPE,
    .type_definition = &__internal_array_test_trie_inner_def,
    .trie_init = noizu_trie__array__init,
    .trie_free = noizu_trie__array__free,
    .trie_validate = noizu_trie__array__validate,
    .trie_advance = noizu_trie__array__advance,
    .trie_tokenize = NULL
};

```

### Tokenizing a String with Array Implementation


```c


//---------------------------------------------------------------
// Custom Sentinel Override to standard Tokenizer Flow
//---------------------------------------------------------------

TRIE_TOKEN array_test_sentinel(TRIE_TOKEN advance_flag, struct noizu_trie_state* state, struct noizu_trie_definition* definition) {

	struct noizu_trie__array__definition* a_trie = (struct noizu_trie__array__definition*)definition->type_definition;
	TRIE_TOKEN t = a_trie->trie[state->position][TRIE_A_TOKEN];
	if (t == ARRAY_JK_CONTENTS) {
		state->token = t;
		state->token_index = state->position;
		state->match_type = TRIE_MATCH;
		return ARRAY_SENTINEL_HALT_ON_CONTENTS;
	}
	if (t == ARRAY_JV_DEGREES_CELSIUS) {
		state->initialized = FALSE;
		state->position = 1;
	}
	return 0;
}





// Runtime Preferences
struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };

// Streaming Input buffer (array struct that contains enough meta data to dynamically reallocate while processing. )
offset_buffer* req = calloc(1, sizeof(offset_buffer));
req->buffer = calloc(256, sizeof(uint8_t));
req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsiuscontentsrelative_humiditydegrees_celsius");
req_position = 0;

// Init State
struct noizu_trie_state state = { 0 };
noizu_trie__init(req, &array_test_trie, options, &state);

// Call entry point noizu_trie__tokenize method, it will forward to per Trie data structure type methods.
TRIE_TOKEN o = noizu_trie__tokenize(&state, &array_test_trie, array_test_sentinel);

if (o & TRIE_ERROR) oh_no();

if (state.match_type == TRIE_MATCH) {
	if (state.trie_token == ARRAY_JK_CONTENTS) {
	    // Input matched ARRAY_JK_CONTENTS or sentinel override action/hint
	}
}
```






## Struct Implementation
```c

noizu_trie_s __internal_struct_test_trie_srr[] = { {.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}
,{.key = '*', .next_sibling = 0, .first_child = 2, .termination_code = 0}
,{.key = 'c', .next_sibling = 3, .first_child = 91, .termination_code = 0}
,{.key = 'd', .next_sibling = 4, .first_child = 10, .termination_code = 0}
,{.key = 'e', .next_sibling = 5, .first_child = 33, .termination_code = 0}
,{.key = 'f', .next_sibling = 6, .first_child = 39, .termination_code = 0}
,{.key = 'h', .next_sibling = 7, .first_child = 51, .termination_code = 0}
,{.key = 'o', .next_sibling = 8, .first_child = 61, .termination_code = 0}
// .
// .
// .
,{.key = 'i', .next_sibling = 0, .first_child = 81, .termination_code = 0}
,{.key = 'd', .next_sibling = 0, .first_child = 82, .termination_code = 0}
,{.key = 'i', .next_sibling = 0, .first_child = 83, .termination_code = 0}
,{.key = 't', .next_sibling = 0, .first_child = 84, .termination_code = 0}
,{.key = 'y', .next_sibling = 0, .first_child = 0, .termination_code = STRUCT_JV_RELATIVE_HUMIDITY}
,{.key = 'h', .next_sibling = 86, .first_child = 88, .termination_code = 0}
,{.key = 'w', .next_sibling = 0, .first_child = 87, .termination_code = 0}
,{.key = 'o', .next_sibling = 0, .first_child = 0, .termination_code = STRUCT_JK_TWO}
,{.key = 'r', .next_sibling = 0, .first_child = 89, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 90, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 0, .termination_code = STRUCT_JK_THREE}
,{.key = 'o', .next_sibling = 0, .first_child = 92, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 93, .termination_code = 0}
,{.key = 't', .next_sibling = 0, .first_child = 94, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 95, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 96, .termination_code = 0}
,{.key = 't', .next_sibling = 0, .first_child = 97, .termination_code = 0}
,{.key = 's', .next_sibling = 0, .first_child = 0, .termination_code = STRUCT_JK_CONTENTS} };

struct noizu_trie__struct__definition __internal_struct_test_trie_inner_def = {
    .trie = __internal_struct_test_trie_srr,
    .trie_length = 98,
};

struct noizu_trie_definition struct_test_trie = {
    .constant = 1,
    .type = TRIE_STRUCT_TYPE,
    .type_definition = &__internal_struct_test_trie_inner_def,
    .trie_init = noizu_trie__struct__init,
    .trie_free = noizu_trie__struct__free,
    .trie_validate = noizu_trie__struct__validate,
    .trie_advance = noizu_trie__struct__advance,
    .trie_tokenize = NULL
};

```




### Tokenizing a String with Struct Implementation


```c

extern offset_buffer* req;
if streaming_input_source(req) {

	// Init State
  struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
	struct noizu_trie_state state = { 0 };
	TRIE_TOKEN o = noizu_trie__init(req, &array_test_trie, options, &state);
  if (o = TRIE_BUFFER_END) {
		wait_more_streaming_input(req);
		o = noizu_trie__init(req, &array_test_trie, options, &state);
		if (o != TRIE_BUFFER_END && state.trie_token  ) {
          switch (state.trie_token) {
						 case HELLO_WORLD_STRING:
						 // do hello world processing.
						 break;
						 case GOOD_NIGHT_MOON:
						 // good night cat.
						 break;
					}   
		}
	}
}
```
