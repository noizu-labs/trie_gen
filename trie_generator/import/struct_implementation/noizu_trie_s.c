/*!
* @file noizu_trie_s.c
* @brief struct encoded static trie implementation.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2019.
*/

#include "noizu_trie_s.h"

TRIE_S_UNIT noizu_trie_s_advance(char k, TRIE_S_UNIT current_node, noizu_trie_s* source) {
	if (current_node == TRIE_NOT_FOUND) return TRIE_NOT_FOUND;
	TRIE_S_UNIT trie_node_index = (*(source + current_node)).first_child;
	while (trie_node_index != TRIE_NOT_FOUND) {
		if ((*(source + trie_node_index)).key == k) {
			return trie_node_index;
		}
		if ((*(source + trie_node_index)).key < k) {
			trie_node_index = (*(source + trie_node_index)).next_sibling;
		}
	}
	return TRIE_NOT_FOUND;
}

TRIE_TOKEN noizu_trie__struct__init(offset_buffer* req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out) {
	if (out == NULL) return TRIE_ARGUMENT_ERROR;
	if (out->type && out->type != TRIE_STRUCT_TYPE) return TRIE_ARGUMENT_ERROR;
	out->type = TRIE_STRUCT_TYPE;

	if (out->type_state == NULL) {
		out->type = (struct noizu_trie__struct__state*)os_zalloc(sizeof(struct noizu_trie__struct__state));
		if (out->type == NULL) return TRIE_ALLOC_FAIL;
		((struct noizu_trie__struct__state*)out->type)->last_token_index = 0;
		((struct noizu_trie__struct__state*)out->type)->token_index = 0;
		((struct noizu_trie__struct__state*)out->type)->position = 1;
	}
	out->req = req;
	out->options = options;
	return TRIE_INITIALIZED;
}

TRIE_TOKEN noizu_trie__struct__validate(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	if (state == NULL) return TRIE_ARGUMENT_ERROR;
	if (state->type != TRIE_ARRAY_TYPE) return TRIE_ARGUMENT_ERROR;
	if (state->type_state == NULL) return TRIE_ARGUMENT_ERROR;
	if (definition == NULL) return TRIE_ARGUMENT_ERROR;
	if (definition->type != TRIE_ARRAY_TYPE) return TRIE_ARGUMENT_ERROR;
	if (definition->type_definition == NULL) return TRIE_ARGUMENT_ERROR;
	if ((state->req->buffer_pos + state->skip_next) == state->req->buffer_size) return TRIE_BUFFER_END;
	if ((state->req->buffer_pos + state->skip_next) > state->req->buffer_size) return TRIE_OVERFLOW_EXIT;
	return TRIE_VALID;
}
TRIE_TOKEN noizu_trie__struct__advance(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	// caller responsible: if (state == NULL) return TRIE_NO_MATCH;

	// Advance position (if halted due to end of stream)
	if (state->skip_next) {
		if ((state->req->buffer_pos + state->skip_next) < state->req->buffer_size) {
			state->req->buffer_pos += state->skip_next;
			state->skip_next = 0;
		}
		else return TRIE_BUFFER_END_ON_SKIP;
	}

	// Advance to next node in trie.
	uint8_t c = *(state->req->buffer + state->req->buffer_pos);
	TRIE_S_UNIT last_index = ((struct noizu_trie__struct__state*)state->type)->position;
	TRIE_S_UNIT next_index = noizu_trie_s_advance(c, last_index, ((struct noizu_trie__struct__definition*)definition->type_definition)->trie);
	if (next_index >= ((struct noizu_trie__struct__definition*)definition->type_definition)->trie_struct_length) {
		state->error_code = TRIE_STRUCT_ACCESS_ERROR;
		state->match_type = TRIE_ABNORMAL_EXIT;
		return TRIE_NO_MATCH;
	}

	// Update State
	((struct noizu_trie__struct__state*)state->type)->position = next_index;
	if (next_index == 0) {
		state->terminator = *(state->req->buffer + state->req->buffer_pos);

		if (state->options.keep_last_token) state->match_type = ((state->terminator == '\0') && state->token) ? TRIE_MATCH : ((state->last_token || state->token) ? TRIE_PARTIAL_MATCH : TRIE_NO_MATCH);
		else {
			// end of input, if not tracking last token grab previous input to check if last char before walking off trie was a valid token.
			if (((struct noizu_trie__struct__definition*)definition->type_definition)->trie[last_index].termination_code) {
				state->token = ((struct noizu_trie__struct__definition*)definition->type_definition)->trie[last_index].termination_code;
				((struct noizu_trie__struct__state*)state->type)->token_index = last_index;
				// TRIE match if end of input, otherwise last match if not end of string but end of trie with last value matching.
				state->match_type = (state->terminator == '\0') ? TRIE_MATCH : TRIE_LAST_MATCH;
			}
			else state->match_type == TRIE_NO_MATCH;
		}
		return (state->terminator == '\0') ? TRIE_END_INPUT_EXIT : TRIE_END_PARSE_EXIT;
	}

	// Track token matches if option set
	if (state->options.keep_last_token) {
		if (state->token) {
			state->last_token = state->token;
			((struct noizu_trie__struct__state*)state->type)->last_token_index = ((struct noizu_trie__struct__state*)state->type)->token_index;
		}
		state->token = (((struct noizu_trie__struct__definition*)definition->type_definition)->trie[next_index].termination_code);
		((struct noizu_trie__struct__state*)state->type)->token_index = next_index;
	}

	// Advance Position/Detect end of buffer state.
	if (state->req->buffer_pos + 1 < state->req->buffer_size) {
		state->req->buffer_pos++;
		return TRIE_CONTINUE;
	}
	else {
		// check for token if end of buffer and not already checked due to keep_last_token flow.
		if (state->options.end_of_buffer_token && !state->options.keep_last_token) {
			state->token = (((struct noizu_trie__struct__definition*)definition->type_definition)->trie[next_index].termination_code);
			((struct noizu_trie__struct__state*)state->type)->token_index = next_index;
			state->match_type == state->token ? TRIE_LAST_MATCH : TRIE_NO_MATCH;
		}
		state->skip_next = 1;
		return TRIE_BUFFER_END;
	}
}
TRIE_TOKEN noizu_trie__struct__tokenize(struct noizu_trie_state* state, struct noizu_trie_definition* definition, tokenizer_sentinel* sentinel) {
	// (caller responsible for validation for optimization) if (state == NULL || definition == NULL || state->type_state == NULL || definition->type_definition == NULL) return TRIE_ARGUMENT_ERROR;
	TRIE_TOKEN sentinel_code, advance;
	while (true) {
		advance = noizu_trie__struct__advance(state, definition);
		if (sentinel && (sentinel_code = (*sentinel)(advance, state, definition))) {
			// sentinel responsible for any state manipulation/token set operations. 
			state->sentinel_exit_code = sentinel_code;
			return TRIE_PARTIAL_SENTINEL_EXIT;
		}
		if (advance != TRIE_CONTINUE) return advance;
	}
}
