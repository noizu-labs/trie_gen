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