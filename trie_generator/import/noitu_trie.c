#include "noizu_trie.h"

TRIE_TOKEN noizu_trie__init(offset_buffer* req, struct noizu_trie_definition* definition, struct noizu_trie_options options, struct noizu_trie_state* out) {
	return definition->trie_init ? definition->trie_init(req, definition, options, out) : TRIE_DEFINITION_ERROR;
}

TRIE_TOKEN noizu_trie__validate(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	return definition->trie_validate ? definition->trie_validate(state, definition) : TRIE_DEFINITION_ERROR;
}

TRIE_TOKEN noizu_trie__advance(struct noizu_trie_state* state, struct noizu_trie_definition* definition) {
	return definition->trie_advance ? definition->trie_advance(state, definition) : TRIE_DEFINITION_ERROR;
}

TRIE_TOKEN noizu_trie__tokenize(struct noizu_trie_state* state, struct noizu_trie_definition* definition, tokenizer_sentinel* sentinel) {
	return definition->trie_tokenize ? definition->trie_tokenize(state, definition, sentinel) : TRIE_DEFINITION_ERROR;
}