/*!
* @file noizu_trie.h
* @brief strategy layer.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2021.
*/

#ifndef __NOIZU_TRIE_H__
#define __NOIZU_TRIE_H__

#ifdef GENERIC_MODE 
typedef unsigned char       uint8_t;
typedef signed char         sint8_t;
typedef signed char         int8_t;
typedef unsigned short      uint16_t;
typedef signed short        sint16_t;
typedef signed short        int16_t;
typedef unsigned int        uint32_t;
typedef signed int          sint32_t;
typedef signed int          int32_t;
typedef signed long long    sint64_t;
typedef unsigned long long  uint64_t;
typedef unsigned long long  u_int64_t;

typedef unsigned char   bool;
#define BOOL            bool
#define true            (1)
#define false           (0)
#define TRUE            true
#define FALSE           false
#define NULL            ((void *)0)


typedef struct offset_buffer {
	uint8_t* buffer; // Current buffer, (may be reallocated between calls).
	uint32_t buffer_size; // Total length of buffer from buffer_pos to end of new data.
	uint32_t allocated_buffer; // Total space allocated for buffer.
	uint32_t buffer_pos; // Current starting position in buffer.
} offset_buffer;

#endif

// Unit Types
#define TRIE_TOKEN uint16_t
#define TRIE_STATE uint8_t
#define TRIE_CHAR_CODE uint8_t

// Hanlders
#define TRIE_STRUCT_TYPE 1
#define TRIE_COMPACT_TYPE 2
#define TRIE_ARRAY_TYPE 3

// Constants
#define TRIE_NO_MATCH 0
#define TRIE_MATCH 1
//! indicates a partial match with input string going past entries in trie.  e.g. searched for apple but no trie entry after 'app' was found.
#define TRIE_PARTIAL_MATCH 2
//! indicates a partial match with input string going past entries in trie.  e.g. searched for apple but no trie entry after 'appl' was found.
#define TRIE_LAST_MATCH 3
//! indicate early exit due to sentinel
#define TRIE_PARTIAL_SENTINEL_EXIT 4


#define TRIE_EXIT 0x10
#define TRIE_END_INPUT_EXIT (TRIE_EXIT | 0x01)
#define TRIE_END_PARSE_EXIT (TRIE_EXIT | 0x02)
//! internal error state
#define TRIE_ABNORMAL_EXIT (TRIE_EXIT | 0x03)
#define TRIE_OVERFLOW_EXIT (TRIE_EXIT | 0x04)


#define TRIE_VALID 0x20
#define TRIE_CONTINUE (TRIE_VALID | 0x01)
#define TRIE_BUFFER_END (TRIE_VALID | 0x02)
#define TRIE_BUFFER_END_ON_SKIP (TRIE_VALID | 0x03)

//! Arguments Invalid
#define TRIE_ERROR 0x40
#define TRIE_ALLOC_FAIL (TRIE_ERROR | 0x01)
#define TRIE_ARRAY_ACCESS_ERROR (TRIE_ERROR | 0x02)
#define TRIE_STRUCT_ACCESS_ERROR TRIE_ARRAY_ACCESS_ERROR
#define TRIE_DEFINITION_ERROR (TRIE_ERROR | 0x03)
#define TRIE_ARGUMENT_ERROR (TRIE_ERROR | 0x04)




#define TRIE_SUCCESS 0x80
#define TRIE_INITIALIZED (TRIE_SUCCESS | 0x01)

/*!
 * @brief string not found special index value.
 * This special trie index functions as termination well to halt processing of non matched input strings.
 * In generated tries trie head begin at index position (1) with a non parsed special token value. (*) by default.
 */
#define TRIE_NOT_FOUND 0




// Forward Declaration
struct noizu_trie_state;
struct noizu_trie_definition;
struct noizu_trie_options;

// custom/special case tokenizer early exit/selection
typedef TRIE_TOKEN(*tokenizer_sentinel)(TRIE_TOKEN advance_flag, struct noizu_trie_state* state, struct noizu_trie_definition* definition);

// Per Implementation callbacks
typedef TRIE_TOKEN(*tokenizer_init)(offset_buffer* req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out);
typedef TRIE_TOKEN(*tokenizer_validate)(struct noizu_trie_state* state, struct noizu_trie_definition* definition);
typedef TRIE_TOKEN(*tokenizer_advance)(struct noizu_trie_state* state, struct noizu_trie_definition* definition);
typedef TRIE_TOKEN(*tokenizer_tokenize)(tokenizer_sentinel* sentinel, struct noizu_trie_state*, struct noizu_trie_definition*);

/*!
* @brief contains type specific trie implementation and handler methods.
*/
typedef struct noizu_trie_definition {
	uint8_t type;
	void* type_definition;

	tokenizer_init trie_init;
	tokenizer_validate trie_validate;
	tokenizer_advance trie_advance;
	tokenizer_tokenize trie_tokenize;
} noizu_trie_definition;

/*!
 * @brief trie config settings.
 */
typedef struct noizu_trie_options {
	uint8_t keep_last_token : 1;
	uint8_t end_of_buffer_token : 1;
} noizu_trie_options;

/*!
 * @brief trie state.
 * Last token, current position on buffer, last termination node, match type, etc.
 */
typedef struct noizu_trie_state {
	uint8_t type;

	// Stream
	offset_buffer* req;
	uint8_t skip_next;

	// Parse Details
	TRIE_STATE match_type;
	TRIE_TOKEN error_code;
	TRIE_TOKEN sentinel_exit_code;
	TRIE_TOKEN token;
	TRIE_TOKEN last_token;
	TRIE_CHAR_CODE terminator; //!< end char / last char.
	unsigned char initialized;

	// Type specific state.
	void* type_state;

	// Options
	noizu_trie_options options;
} noizu_trie_state;

/*!
 * Init trie state for processing.
 */
TRIE_TOKEN noizu_trie__init(offset_buffer *req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out);

/*!
 * Validate definition and state
 */
TRIE_TOKEN noizu_trie__validate(struct noizu_trie_state* state, struct noizu_trie_definition* definition);

/*!
 * Advance trie one character of input.
 */
TRIE_TOKEN noizu_trie__advance(struct noizu_trie_state* state, struct noizu_trie_definition* definition);

/*!
 * Tokenize input stream.
 */
TRIE_TOKEN noizu_trie__tokenize(struct noizu_trie_state* state, struct noizu_trie_definition* definition, tokenizer_sentinel* sentinel);

#endif