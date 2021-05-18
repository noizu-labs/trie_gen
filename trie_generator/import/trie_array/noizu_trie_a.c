/*!
* @file noizu_trie_a.c
* @brief array encoded static trie implementation.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2019.
*/


#include "../noizu_trie.h"
#include "noizu_trie_a.h"


/*!
 * @brief advance position through trie structure by find sibling or direct child matching index node. Return TRIE_NOT_FOUND indicator if current node not found or matching entry exists. 
 */
TRIE_A_UNIT noizu_trie_a_advance(char key, TRIE_A_UNIT current_node, noizu_trie_a source[]) {
	if (current_node == TRIE_NOT_FOUND) return TRIE_NOT_FOUND;
	TRIE_A_UNIT trie_node = source[current_node][TRIE_A_CHILD];
	while (trie_node != TRIE_NOT_FOUND) {
		if (source[trie_node][TRIE_A_CHARACTER] == key) {
			return trie_node;
		}
		if (source[trie_node][TRIE_A_CHARACTER] < key) {
			trie_node = source[trie_node][TRIE_A_SIBLING];
		}
		else {
			return TRIE_NOT_FOUND;
		}
	}
	return TRIE_NOT_FOUND;
}


TRIE_TOKEN noizu_trie__array__init(offset_buffer* req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out) {
	if (out->type_state && out->type && out->type != TRIE_ARRAY_TYPE) return TRIE_ARGUMENT_ERROR__INVALID_TYPE_STATE;
	out->type = TRIE_ARRAY_TYPE;
	if (out->type_state) return TRIE_ARGUMENT_ERROR__INVALID_TYPE_STATE;
	out->position = 1;
	return TRIE_INITIALIZED;
}

TRIE_TOKEN noizu_trie__array__free(struct noizu_trie_state* state, struct noizu_trie_definition* definition, TRIE_TOKEN mode) {
	if (state == NULL && definition == NULL) return TRIE_SUCCESS;
	if (mode & TRIE_FREE_DEFINITION__INNER) {
		if (definition && definition->type_definition) {
			if (definition->type != TRIE_STRUCT_TYPE) return TRIE_ARGUMENT_ERROR__INVALID_TYPE_STATE;
			if (definition->constant) return TRIE_ERROR_DEALLOC_CONSTANT_DEFINITION;
			os_free((struct noizu_trie__array__definition*)definition->type_definition);
			definition->type_definition = NULL;
		}
	}
	return TRIE_SUCCESS;
}

TRIE_TOKEN noizu_trie__array__validate(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	if (state->type != TRIE_ARRAY_TYPE) return TRIE_ARGUMENT_ERROR__INVALID_TYPE_STATE;
	if (definition->type != TRIE_ARRAY_TYPE) return TRIE_ARGUMENT_ERROR__INVALID_TYPE_DEFINITION;
	return TRIE_VALID_EXIT;
}

TRIE_TOKEN noizu_trie__array__advance(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	// Advance position (if halted due to end of stream)
	if (state->skip_next) {
		if ((state->req->buffer_pos + state->skip_next) < state->req->buffer_size) {
			state->req->buffer_pos += state->skip_next;
			state->skip_next = 0;
		} else return TRIE_BUFFER_END_ON_SKIP;
	}

	// Advance to next node in trie.
	TRIE_CHAR_CODE c = *(state->req->buffer + state->req->buffer_pos);
	TRIE_A_UNIT last_index = state->position;
	TRIE_A_UNIT next_index = (state->options.hard_delim && state->options.delimiter == c) ? 0 : noizu_trie_a_advance(c, last_index, ((struct noizu_trie__array__definition*)definition->type_definition)->trie);
	if (next_index >= ((struct noizu_trie__array__definition*)definition->type_definition)->trie_length) {
		state->error_code = TRIE_ARRAY_ACCESS_ERROR;
		state->match_type = TRIE_ABNORMAL_EXIT;
		return TRIE_NO_MATCH;
	}

	// Update State
	state->position = next_index;
	if (next_index == 0) {
		state->terminator = c;
		if (state->options.keep_last_token) state->match_type = ((state->terminator == '\0' || state->terminator == state->options.delimiter) && state->token) ? TRIE_MATCH : ((state->last_token || state->token) ? TRIE_PARTIAL_MATCH : TRIE_NO_MATCH);
		else {
			// end of input, if not tracking last token grab previous input to check if last char before walking off trie was a valid token.
			if (((struct noizu_trie__array__definition*)definition->type_definition)->trie[last_index][TRIE_A_TOKEN]) {
				state->token = ((struct noizu_trie__array__definition*)definition->type_definition)->trie[last_index][TRIE_A_TOKEN];
				state->token_index = last_index;
				state->token_pos = state->req->buffer_pos;
				// TRIE match if end of input, otherwise last match if not end of string but end of trie with last value matching.
				state->match_type = (state->terminator == '\0' || state->terminator == state->options.delimiter) ? TRIE_MATCH : TRIE_LAST_MATCH;
			}
			else state->match_type = TRIE_NO_MATCH;			
		}
		if (state->terminator == '\0') return TRIE_END_INPUT_EXIT;
		else if (state->terminator == state->options.delimiter) return TRIE_DELIM_EXIT;
		else return TRIE_END_PARSE_EXIT;
	}

	// Track token matches if option set
	if (state->options.keep_last_token) {
		if (state->token) {
			state->last_token = state->token;
			state->last_token_index = state->token_index;
			state->last_token_pos = state->req->buffer_pos;
		}
		state->token = (((struct noizu_trie__array__definition*)definition->type_definition)->trie[next_index][TRIE_A_TOKEN]);
		state->token_index = next_index;
		state->token_pos = state->req->buffer_pos;
	}

	// Advance Position/Detect end of buffer state.
	if (state->req->buffer_pos + 1 < state->req->buffer_size) {
		state->req->buffer_pos++;
		return TRIE_CONTINUE;
	}
	else {
		// check for token if end of buffer and not already checked due to keep_last_token flow.
		if (state->options.end_of_buffer_token && !state->options.keep_last_token) {
			state->token = (((struct noizu_trie__array__definition*)definition->type_definition)->trie[next_index][TRIE_A_TOKEN]);
			state->token_index = state->token ? next_index : 0;
			state->token_pos = state->token ? state->req->buffer_pos : 0;
			state->match_type = state->token ? TRIE_LAST_MATCH : TRIE_NO_MATCH;
		}
		state->skip_next = 1;
		return TRIE_BUFFER_END;
	}
}
