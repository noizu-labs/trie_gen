/*!
* @file noizu_trie_c.c
* @brief struct encoded static trie implementation.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2019.
*/

#include "noizu_trie_c.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

TRIE_C_UNIT EXTRACT_TRIE_VALUE(TRIE_C_UNIT index, TRIE_C_UNIT record_size, TRIE_C_UNIT gap, TRIE_C_UNIT run, TRIE_C_CHAR* char_map, TRIE_C_UNIT len) {
	unsigned int bit = (index * record_size) + gap;
	unsigned int bit_offset = bit % 8;
	unsigned int byte = bit / 8;

	unsigned int mask = (1 << ((8 - bit_offset))) - 1;
	//printf("MASK = 0x%.8X\r\n", mask);
	unsigned int raw = ( (byte < len ? char_map[byte] : 0) & mask);
	//printf("Byte = 0x%.8X\r\n", char_map[byte]);
	//printf("RAW = 0x%.8X\r\n", raw);
	unsigned int scrape = 8 - bit_offset;
	while (scrape < run) {
		byte++;
		raw = (raw << 8) | (byte < len ? char_map[byte] : 0);
		scrape += 8;
		//printf("Byte = 0x%.8X\r\n", char_map[byte]);
		//printf("RAW = 0x%.8X\r\n", raw);
	}
    // unshift overrun 
	raw = raw >> (scrape - run);
	//printf("Fin RAW = 0x%.8X\r\n--------------\r\n", raw);
	//printf("\r\n");
	return raw;
}

#define EXTRACT_CHILD_JUMP(index, trie) EXTRACT_TRIE_VALUE((index), (trie)->bit_length, (trie)->bit_length__child_relative_offset, (trie)->bit_length__child_relative_index, (trie)->trie_raw, (trie)->trie_raw_length)
#define EXTRACT_SIB_JUMP(index, trie) EXTRACT_TRIE_VALUE((index), (trie)->bit_length, (trie)->bit_length__character_code, (trie)->bit_length__sibling_relative_index, (trie)->trie_raw, (trie)->trie_raw_length)
#define EXTRACT_CHAR(index, trie) EXTRACT_TRIE_VALUE((index), (trie)->bit_length, 0, (trie)->bit_length__character_code, (trie)->trie_raw, (trie)->trie_raw_length)

/*!
 * @brief advance position through trie structure by find sibling or direct child matching index node. Return TRIE_NOT_FOUND indicator if current node not found or matching entry exists.
 * @return still on trie
 */
TRIE_C_TOKEN noizu_trie_compact_advance(TRIE_C_CHAR k, noizu_trie_compact_state* state, noizu_trie_compact_definition* trie) {		
	TRIE_C_TOKEN index;
	TRIE_C_TOKEN advance;
	TRIE_C_UNIT raw_char;
	TRIE_C_UNIT scan_for = (*trie->char_code)(k);

	// 1. Advance to child if TRIE_INDEX != TRIE_NOT_FOUND
	if (state->trie_index == TRIE_NOT_FOUND && state->init) return TRIE_NOT_FOUND;
	state->init = 1;
	index = state->trie_index;
	advance = EXTRACT_CHILD_JUMP(state->trie_index, trie);
		
	if (scan_for == TRIE_NOT_FOUND) return TRIE_NOT_FOUND;
	

	// 2. Find sibling that matches input. 	
	while (advance != TRIE_NOT_FOUND) {
		index += advance;
		raw_char = EXTRACT_CHAR(index, trie);
		if (raw_char == TRIE_NOT_FOUND || raw_char > trie->characters) return TRIE_NOT_FOUND;
		if (raw_char == scan_for) {
			state->last_index = state->trie_index;
			state->trie_index = index;
			return TRIE_PARTIAL_MATCH;
		}
		if (trie->char_map[raw_char - 1] < trie->char_map[scan_for - 1]) {
			advance = EXTRACT_SIB_JUMP(index, trie);
		}
		else {
			return TRIE_NOT_FOUND;
		}
	}
	return TRIE_NOT_FOUND;
}

/*!
 * @brief tokenize input string, parses full string, 
 * if walks past trie table set terminator character and previous token
 * so caller can check if terminal valid for end of token.  e.g.  "apple+" when we want to match on apple, tokenizer returns token for apple and indicates we excited on '+'
 */
TRIE_C_TOKEN noizu_trie_compact_tokenize(TRIE_C_CHAR* input, TRIE_C_CHAR track_last_token, noizu_trie_c_tokenizer_sentinel* sentinel, noizu_trie_compact_state* state, noizu_trie_compact_definition* trie) {
	if (!input) return TRIE_NOT_FOUND;
	TRIE_C_UNIT m = TRIE_NOT_FOUND;
	TRIE_C_UNIT s = 0;
	TRIE_C_UNIT offset = 0;
	while (*(input + offset) != '\0') {
		m = noizu_trie_compact_advance(*(input + offset), state, trie);
		if (m != TRIE_PARTIAL_MATCH) break;		
		if (track_last_token) m = (*trie->set_node_token)(1, state, trie);
		if (sentinel && (*sentinel)(state, trie)) {
			s = TRIE_PARTIAL_SENTINEL_EXIT;
			break;
		}
		offset++;
	}

	if (s != 0) return s;
	else {
		// determine effective match_type - e.g. end of string or end of valid string but has match. 
		if (m != TRIE_PARTIAL_MATCH) state->match_type = (* trie->set_node_token)(0, state, trie);
		else if (!track_last_token) {
			// check previous and current position to make life simple.
			TRIE_C_UNIT t = state->token_index;
			if (state->last_index) {
				state->token_index = state->last_index;
				m = (*trie->set_node_token)(1, state, trie);
				state->token_index = t;
				state->match_type = (*trie->set_node_token)(1, state, trie);
				if (state->match_type != TRIE_PARTIAL_MATCH && m == TRIE_PARTIAL_MATCH) {
					state->match_type = m;
				}
			}
			else {
				state->match_type = (*trie->set_node_token)(1, state, trie);
			}
			
			
		}
		else state->match_type = m; // track_last_token response
		// sentinel responsible for setting these values if caller requires them.
		state->last_index = state->trie_index;
		state->terminator = *(input + offset);
		state->input_index = offset;
		state->input_position = (input + offset);
		return state->match_type; // use will have to check if terminator was valid and promote to TRIE_MATCH if so.
	}
}
