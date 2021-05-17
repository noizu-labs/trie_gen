/*!
* @file noizu_trie_c.h
* @brief ultra compact struct encoded static trie implementation.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2021.
*/

#ifndef __NOIZU_TRIE_C_H__
#define __NOIZU_TRIE_C_H__

#include "noizu_trie.h"

#ifndef TRIE_C_CHAR
/*!
 * character type, may be overridden if using unicode strings.
 */
#define TRIE_C_CHAR unsigned char
#endif

#ifndef TRIE_C_UNIT
 /*!
  * @brief trie list index unit
  */
#define TRIE_C_UNIT TRIE_TOKEN
#endif

#ifndef TRIE_C_TOKEN
/*!
 * @breif trie token unit
 */
#define TRIE_C_TOKEN TRIE_TOKEN
#endif

#ifndef TRIE_C_BIT_POS
 /*!
  * @brief trie list index unit
  */
#define TRIE_C_BIT_POS uint32_t
#endif







typedef struct noizu_trie_compact_definition;
typedef struct noizu_trie_compact_state;

  /*!
   * Optional tokenizer sentinel to allow premature exits when tokenizing an input string.
   * @param noizu_trie_c_out* current position details
   * @param noizu_trie_c_compat* trie structure
   * @return true early exit, false continue processing
   */
typedef TRIE_C_TOKEN(*noizu_trie_c_tokenizer_sentinel)(struct noizu_trie_compact_state*, struct noizu_trie_compact_definition*);

/*
 *  @brief function to map input characters to compact format. 0 returned to indicate no encoding found. Positive return value indicates index position of character (plus 1).
 */
typedef TRIE_C_CHAR(*noizu_trie_c_token_code)(TRIE_C_CHAR);

/*!
 * @brief set token, token_lookup_memo and token_index of state pointer.
 * @param clear - set token and token_index to zero if no match.
 * @return true - token found, false - no token found
 */
typedef TRIE_C_TOKEN(*noizu_trie_set_token)(TRIE_C_UNIT, struct noizu_trie_compact_state*, struct noizu_trie_compact_definition*);

/*!
* @brief super compact trie tree definition. Trie tree and token's are encoded in binary data stream of variable width depending on characteristics of input.
 */
typedef struct noizu_trie_compact_definition {
	TRIE_C_UNIT size; //!< total nodes in trie tree
	TRIE_C_UNIT tokens; //!< total tokens defined
	TRIE_C_UNIT characters; //!< total unique characters in trie.
	TRIE_C_UNIT bit_length; //!< total record with
	TRIE_C_UNIT bit_length__character_code; //!< number of bits used to encode each character. 
	TRIE_C_UNIT bit_length__sibling_relative_index;  //!< number of bits used to encode distance (in nodes) to next sibling
	TRIE_C_UNIT bit_length__child_relative_offset; //!< to avoid calculations., just char + sib length
	TRIE_C_UNIT bit_length__child_relative_index; //!< number of bits used to encode distance (in nodes) to next child
	TRIE_C_UNIT* trie_raw; //!< binary stream of tokens in form of  {char_bits, next_sibling_bits, next_child_bits}
	TRIE_C_UNIT trie_raw_length; //!< total bytes to avoid overruns.
	TRIE_C_CHAR* char_map; //!< character look up table, the trie for "Hello World" for example would have a char map of ['H', 'e', 'l', 'o', 'W', 'r', 'd'] and would use 3 bits to encode each character
	noizu_trie_set_token set_node_token; //!< map node index to token function, 
	noizu_trie_c_token_code char_code;
} noizu_trie_compact_definition;

/*!
 * @brief trie transversal position
 */
typedef struct noizu_trie_compact_state {
	TRIE_C_UNIT match_type;
	TRIE_C_CHAR character;
	TRIE_C_UNIT trie_index;
	TRIE_C_UNIT last_index; //!< previous position on trie

	TRIE_C_UNIT sentinal; //!< if early exit triggered by sentinel.	

	TRIE_C_UNIT token_index; //<! position of node token was taken from
	TRIE_C_TOKEN token; //!< last matched token, if match is false our input string did not have an exact match.  A scan for apple if only 'apple' was on the trie would return match=false, token=token_for_appl

	TRIE_C_UNIT last_token_index;
	TRIE_C_TOKEN last_token;

	TRIE_C_CHAR* input_position;
	TRIE_C_UNIT input_index;
	TRIE_C_CHAR terminator;
	TRIE_C_CHAR init;
} noizu_trie_compact_state;

/*!
 * @brief advance position through trie structure by find sibling or direct child matching index node. Return TRIE_NOT_FOUND indicator if current node not found or matching entry exists.
 * @return still on trie
 */
TRIE_C_TOKEN noizu_trie_compact_advance(TRIE_C_CHAR k, noizu_trie_compact_state* state, noizu_trie_compact_definition* trie);

/*!
 * @brief tokenize input string, parses full string, if walks past trie table record terminator character and previous token so caller can check if terminal valid for end of token.  e.g.  "apple+" when we want to match on apple, tokenizer returns token for apple and indicates we excited on '+'
 */
TRIE_C_TOKEN noizu_trie_compact_tokenize(TRIE_C_CHAR* input, TRIE_C_CHAR track_last_token, noizu_trie_c_tokenizer_sentinel* sentinel, noizu_trie_compact_state* state, noizu_trie_compact_definition* trie);


TRIE_TOKEN noizu_trie__compact__init(offset_buffer* req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out);
TRIE_TOKEN noizu_trie__compact__validate(struct noizu_trie_state* out, struct noizu_trie_definition* definition);
TRIE_TOKEN noizu_trie__compact__advance(struct noizu_trie_state* state, struct noizu_trie_definition* definition);
TRIE_TOKEN noizu_trie__compact__tokenize(struct noizu_trie_state* state, struct noizu_trie_definition* definition, tokenizer_sentinel* sentinel);




#endif