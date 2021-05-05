/*!
* @file trie_generator.c
*
* @author Keith Brings
* @repo github.com/noizu/trie_gen
* @copyright Noizu Labs, Inc. 2021.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie_generator.h";





//---------------------------------------------------
// Trie Transversal & Construction
//---------------------------------------------------


void insert(char* token, char* termination_code, NoizuAutoTrie* root) {
	NoizuAutoTrie* p = root;
	while (*token != '\0') {
		p = obtain_child(*token, p);
		token++;
	}

	if (p) {
		if (p->termination_code) {
			printf("Error| Path Already Set %s, %s\n", token, p->termination_code);
		}
		//printf("Termination Code = %s, %d\n", termination_code, strlen(termination_code));
		p->termination_code = (char*)malloc((strlen(termination_code) + 1));
		strcpy_s(p->termination_code, strlen(termination_code) + 1, termination_code);
	}
}

NoizuAutoTrie* child(char k, NoizuAutoTrie* parent) {
	if (parent->first_child) {
		return sibling(k, parent);
	}
	else {
		return NULL;
	}
}

NoizuAutoTrie* obtain_child(char k, NoizuAutoTrie* parent) {
	// std::cout << "obtain_child 1." << k << "\n";
	if (parent->first_child) {
		// std::cout << "obtain_child 2." << k << "\n";
		return obtain_sibling(k, parent);
	}
	else {
		// std::cout << "obtain_child 3." << k << "\n";
		parent->first_child = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
		if (parent->first_child) {
			memset(parent->first_child, 0, sizeof(NoizuAutoTrie));
			parent->first_child->key = k;
			return parent->first_child;
		}
		else { return NULL; }
	}
}

NoizuAutoTrie* sibling(char k, NoizuAutoTrie* parent) {
	if (parent->first_child) {
		NoizuAutoTrie* p = parent->first_child;

		while (TRUE) {
			if (p->key == k) {
				return p;
			}
			else if (p->key < k) {
				if (p->next_sibling) {
					p = p->next_sibling;
				}
				else {
					return NULL;
				}
			}
			else if (p->key > k) {
				return NULL;
			}
		}
	}
	else {
		return NULL;
	}
}

NoizuAutoTrie* obtain_sibling(char k, NoizuAutoTrie* parent) {
	if (parent->first_child) {
		// std::cout << "obtain_sibling 1. " << k << "\n";
		NoizuAutoTrie* p = parent->first_child;
		NoizuAutoTrie* p2 = NULL;

		while (TRUE) {
			// std::cout << "obtain_sibling 2. " << k << " ? " << p->key << "\n";
			if (p->key == k) {
				// std::cout << "obtain_sibling 3. " << k << " = " << p->key << "\n";
				return p;
			}
			else if (p->key < k) {
				// std::cout << "obtain_sibling 3. " << k << " < " << p->key << "\n";
				if (p->next_sibling) {
					// std::cout << "obtain_sibling 4. " << k << " < " << p->key << "\n";
					p2 = p;
					p = p->next_sibling;
				}
				else {
					// std::cout << "obtain_sibling 5. " << k << " < " << p->key << "\n";
					p->next_sibling = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
					if (p->next_sibling) {
						memset(p->next_sibling, 0, sizeof(NoizuAutoTrie));
					}
					p->next_sibling->key = k;
					return p->next_sibling;
				}
			}
			else if (p->key > k) {
				// std::cout << "obtain_sibling 3. " << k << " > " << p->key << "\n";
				if (p2) {
					// std::cout << "obtain_sibling 6. " << k << " > " << p->key << "\n";
					p2->next_sibling = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
					if (p2->next_sibling) {
						memset(p2->next_sibling, 0, sizeof(NoizuAutoTrie));
					}
					p2->next_sibling->next_sibling = p;
					p2->next_sibling->key = k;
					p2->next_sibling->termination_code = 0;
					return p2->next_sibling;
				}
				else {
					// std::cout << "obtain_sibling 7. " << k << " > " << p->key << "\n";
					parent->first_child = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
					if (parent->first_child) {
						memset(parent->first_child, 0, sizeof(NoizuAutoTrie));
					}
					parent->first_child->next_sibling = p;
					parent->first_child->key = k;
					return parent->first_child;
				}
			}
		}
	}
	else {
		// std::cout << "obtain_sibling 8. " << k << "\n";
		parent->first_child = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));
		if (parent->first_child) {
			memset(parent->first_child, 0, sizeof(NoizuAutoTrie));
		}
		parent->first_child->key = k;
		return parent->first_child;
	}
}

NoizuAutoTrie* advance(char k, NoizuAutoTrie* position) {
	if (position) {
		return child(k, position);
	}
	else {
		return NULL;
	}
}


//---------------------------------------------------
// Data Prep needed for output.
//---------------------------------------------------

NoizuAutoTrie* gen_prep(NoizuAutoTrie* root) {
	// std::cout << "gen_prep" << "\n";
	NoizuAutoTrie* p = root;
	p->index = 1;
	p = gen_prep_siblings(root, p);
	p = gen_prep_children(root, p);


	return p;
}

void gen_prep_details(NoizuAutoTrie* n, noizu_auto_trie_compact_details* details) {
	while (n) {

		// Sibling Distance.
		if (n->next_sibling) {
			n->relative_sibling_index = n->next_sibling->index - n->index;
			details->largest_sibling_jump = (n->relative_sibling_index > details->largest_sibling_jump) ? n->relative_sibling_index : details->largest_sibling_jump;
		}

		// Child Distance.
		if (n->first_child) {
			n->relative_child_index = n->first_child->index - n->index;
			details->largest_child_jump = (n->relative_child_index > details->largest_child_jump) ? n->relative_child_index : details->largest_child_jump;
		}

		// Character Map
		if (details->char_reverse[n->key] == 0) {
			details->char_reverse[n->key] = details->char_count + 1;
			details->char_map[details->char_count] = n->key;
			details->char_count++;
		}

		// Token Map
		if (n->termination_code) {
			details->token_count++;
			if (details->token_map == NULL) {
				details->token_map = (noizu_auto_trie_compact_token_node*)malloc(sizeof(noizu_auto_trie_compact_token_node));
				memset(details->token_map, 0, sizeof(noizu_auto_trie_compact_token_node));
				details->token_map_tail = details->token_map;
			}
			else {
				details->token_map_tail->next = (noizu_auto_trie_compact_token_node*)malloc(sizeof(noizu_auto_trie_compact_token_node));
				memset(details->token_map_tail->next, 0, sizeof(noizu_auto_trie_compact_token_node));
				details->token_map_tail = details->token_map_tail->next;
			}
			details->token_map_tail->node_index = n->index;
			details->token_map_tail->token = n->termination_code;
		}

		details->node_count++;
		n = n->index_route;
	}
}

NoizuAutoTrie* gen_prep_children(NoizuAutoTrie* n, NoizuAutoTrie* index) {
	// std::cout << "gen_prep_children" << "\n";
	if (n->first_child) {
		// std::cout << "gen_prep_children+" << "\n";
		n->first_child->index = index->index + 1;
		index->index_route = n->first_child;
		index = n->first_child;
		index = gen_prep_siblings(index, index);
		index = gen_prep_children(n->first_child, index);
	}

	return index;
}

NoizuAutoTrie* gen_prep_siblings(NoizuAutoTrie* n, NoizuAutoTrie* index) {
	// std::cout << "gen_prep_siblings " << n->key << "\n";
	NoizuAutoTrie* p = n->next_sibling;
	while (p) {
		// std::cout << "gen_prep_siblings + " << p->key << "\n";
		p->index = index->index + 1;
		index->index_route = p;
		index = p;
		p = p->next_sibling;
	}
	p = n->next_sibling;
	while (p) {
		// std::cout << "gen_prep_siblings ++ " << p->key << "\n";
		index = gen_prep_children(p, index);
		p = p->next_sibling;
	}
	return index;
}

NoizuAutoTrie* gen_prep_depth_first(NoizuAutoTrie* root) {
	// std::cout << "gen_prep" << "\n";
	NoizuAutoTrie* p = root;
	p->index = 1;
	p = gen_prep_children_depth_first(root, p);
	p = gen_prep_siblings_depth_first(root, p);

	return p;
}

NoizuAutoTrie* gen_prep_children_depth_first(NoizuAutoTrie* n, NoizuAutoTrie* index) {
	// std::cout << "gen_prep_children" << "\n";
	if (n->first_child) {
		// std::cout << "gen_prep_children+" << "\n";
		n->first_child->index = index->index + 1;
		index->index_route = n->first_child;
		index = n->first_child;
		index = gen_prep_children_depth_first(n->first_child, index);
		index = gen_prep_siblings_depth_first(n->first_child, index);
	}

	return index;
}

NoizuAutoTrie* gen_prep_siblings_depth_first(NoizuAutoTrie* n, NoizuAutoTrie* index) {
	// std::cout << "gen_prep_siblings " << n->key << "\n";
	NoizuAutoTrie* p = n->next_sibling;
	while (p) {
		// std::cout << "gen_prep_siblings + " << p->key << "\n";
		p->index = index->index + 1;
		index->index_route = p;
		index = p;
		index = gen_prep_children_depth_first(p, index);
		p = p->next_sibling;
	}
	return index;
}


//---------------------------------------------------
// Generate
//---------------------------------------------------


void gen_array_format(char* genVar, NoizuAutoTrie* index, FILE* fptr) {
	fprintf(fptr, "\n\n#include \"noizu_trie_a.h\"\n\nconst noizu_trie_a %s[] = {\n", genVar);
	fprintf(fptr, "\t{0, 0, 0, 0}");
	while (index) {
		unsigned int next = index->next_sibling ? index->next_sibling->index : 0;
		unsigned int child = index->first_child ? index->first_child->index : 0;
		char key = index->key;
		fprintf(fptr, ",\n\t{'%C', %u, %u, %s}", key, next, child, (index->termination_code ? index->termination_code : "0"));
		// std::cout << ",\n" << "{.key = '" << key << "', .next_sibling = " << next << ", .first_child = " << child << ", .termination_code = " << termination_code << "}";
		index = index->index_route;
	}
	fprintf(fptr, "\n};\n");
}

void gen_compact_format(char* genVar, NoizuAutoTrie* index, noizu_auto_trie_compact_details* details, FILE* fptr) {
	unsigned int i;
	fprintf(fptr, "\n\n#include \"noizu_trie_compact.h\"\n\n");
	// Output Meta Details

	// Char Map
	fprintf(fptr, "\n\n// %s: CharMap\n", genVar);
	fprintf(fptr, "TRIE_C_CHAR %s_cm(TRIE_C_CHAR c) {\n", genVar);
	for (i = 0; i < details->char_count; i++) {
		unsigned int c = details->char_map[i];
		if (i == 0) {
			fprintf(fptr, "    if (c == '%c') return %d;\n", c, i + 1);
		}
		else {
			fprintf(fptr, "    if (c == '%c') return %d;\n", c, i + 1);
		}

	}
	fprintf(fptr, "    return 0;\n}\n\n");

	fprintf(fptr, "TRIE_C_CHAR %s_chars[] = {", genVar);
	for (i = 0; i < details->char_count; i++) {
		unsigned int c = details->char_map[i];
		if (i == 0) {
			fprintf(fptr, "'%c'", c);
		}
		else {
			fprintf(fptr, ", '%c'", c);
		}
	}
	fprintf(fptr, "};");


	// Token Set
	fprintf(fptr, "\n\n// %s: SetToken\n", genVar);
	fprintf(fptr, "TRIE_C_TOKEN %s_token(TRIE_C_TOKEN clear, noizu_trie_compact_state* state, noizu_trie_compact_definition* definition) {\n    TRIE_C_TOKEN has_token = 1;\n    TRIE_C_TOKEN token = 0;\n    TRIE_C_UNIT index = state->trie_index;\n", genVar);
	noizu_auto_trie_compact_token_node* t = details->token_map;
	int f = 1;
	while (t) {
		if (f) {
			f = 0;
			fprintf(fptr, "    if (index == %d) token = %s;\n", t->node_index - 1, t->token);
		}
		else {
			fprintf(fptr, "    else if (index == %d) token = %s;\n", t->node_index - 1, t->token);
		}
		t = t->next;
	}
	fprintf(fptr, "    else has_token = 0;\n\n");



	
	fprintf(fptr, "    if (((clear && !has_token) || has_token) && state->token != TRIE_NOT_FOUND) {\n        state->last_token = state->token;\n        state->last_token_index == state->token_index;\n    }\n");
	fprintf(fptr, "    if (clear && !has_token) {\n        state->token = 0;\n        state->token_index = 0;\n    }\n");

	fprintf(fptr, "    if (clear && !has_token) {\n        state->token = 0;\n        state->token_index = 0;\n    }\n");
	fprintf(fptr, "    if (has_token) {\n    state->token = token;\n    state->token_index = state->trie_index;\n    }\n");
	fprintf(fptr, "    return (has_token ? TRIE_PARTIAL_MATCH : TRIE_NOT_FOUND);\n}\n\n");

	// Nodes
	unsigned int field_width = log2(details->char_count) + log2(details->largest_sibling_jump) + 1; // log2(details->largest_child_jump);
	unsigned int _tb = field_width * details->node_count;
	unsigned int total_bytes = ((_tb - (_tb % 8)) / 8) + ((_tb % 8) ? 1 : 0);

	unsigned char* raw = malloc(total_bytes);
	if (raw == NULL) return;
	memset(raw, 0, total_bytes);

	unsigned int char_bits = log2(details->char_count);
	unsigned int jump_bits = log2(details->largest_sibling_jump);
	unsigned long bit = 0;
	NoizuAutoTrie* n = index;
	while (n) {
		unsigned char set = 0;
		unsigned int j, _byte, _byte_bit;

		// apply char code bits
		unsigned int c = details->char_reverse[n->key];
		for (j = 0; j < char_bits; j++) {
			_byte = (bit - (bit % 8)) / 8;
			_byte_bit = (bit % 8);

			set = c & (1 << (char_bits - j - 1));
			if (set) {
				raw[_byte] |= (1 << (7 - _byte_bit));
			}
			bit++;
		}

		// apply sibling jump code bits
		c = n->relative_sibling_index;
		for (j = 0; j < jump_bits; j++) {
			_byte = (bit - (bit % 8)) / 8;
			_byte_bit = (bit % 8);

			set = c & (1 << (jump_bits - j - 1));
			if (set) {
				raw[_byte] |= (1 << (7 - _byte_bit));
			}
			bit++;
		}

		// apply child bit
		if (n->relative_child_index) {
			_byte = (bit - (bit % 8)) / 8;
			_byte_bit = (bit % 8);
			raw[_byte] |= (1 << (7 - _byte_bit));
		}
		bit++;
		n = n->index_route;
	}

	fprintf(fptr, "\n\n// %s: Node Binary| Bits per field = %d, required = %d\n", genVar, field_width, total_bytes);
	fprintf(fptr, "unsigned char %s_node_map[] = {\n", genVar);
	for (i = 0; i < total_bytes; i++) {
		fprintf(fptr, "%#04X,", raw[i]);
		if (i != 0 && ((i + 1) % 4) == 0) fprintf(fptr, "\n");
	}
	fprintf(fptr, "};\n");
	free(raw);



	fprintf(fptr, "\n\n// %s: Compact Trie Definition, max_sibling_jump=%d rows\n", genVar, details->largest_sibling_jump);
	fprintf(fptr, "noizu_trie_compact_definition %s = {\n", genVar);
	fprintf(fptr, "    .size = %d,\n", details->node_count);
	fprintf(fptr, "    .tokens = %d,\n", details->token_count);
	fprintf(fptr, "    .characters = %d,\n", details->char_count);
	fprintf(fptr, "    .bit_length__character_code = %d,\n", log2(details->char_count));
	fprintf(fptr, "    .bit_length__sibling_relative_index = %d,\n", log2(details->largest_sibling_jump));
	// Always 1 bit 
	fprintf(fptr, "    .bit_length__child_relative_index = %d,\n", log2(details->largest_child_jump));
	fprintf(fptr, "    .bit_length__child_relative_offset = %d,\n", log2(details->char_count) + log2(details->largest_sibling_jump));
	fprintf(fptr, "    .bit_length = %d,\n", log2(details->char_count) + log2(details->largest_sibling_jump) + log2(details->largest_child_jump));
	fprintf(fptr, "    .trie_raw = %s_node_map,\n", genVar);
	fprintf(fptr, "    .trie_raw_length = %d,\n", total_bytes);

	
	fprintf(fptr, "    .char_map = %s_chars,\n", genVar);
	fprintf(fptr, "    .set_node_token = %s_token,\n", genVar);
	fprintf(fptr, "    .char_code = %s_cm\n", genVar);
	fprintf(fptr, "};\n");



	n = index;
	fprintf(fptr, "\n\n\n\n// %s: Node Binary| Bits per field = %d, required = %d\n", genVar, field_width, total_bytes);
	fprintf(fptr, " /*\n");
	fprintf(fptr, " * %s_node_map_encoding = [\n", genVar);
	while (n) {
		unsigned int c = details->char_reverse[n->key];
		fprintf(fptr, " * index %d| char:%c(%d), sib_jump: %d, child_jump: %d|%s,\n", n->index - 1, n->key, c, n->relative_sibling_index, n->relative_child_index, n->termination_code ? n->termination_code : "");
		n = n->index_route;
	}
	fprintf(fptr, " * ];\n");
	fprintf(fptr, " */\n");



}

void gen_struct_format(char* genVar, NoizuAutoTrie* index, FILE* fptr) {
	fprintf(fptr, "\n\n#include \"noizu_trie_s.h\"\n\nnoizu_trie_s %s[] = {", genVar);
	fprintf(fptr, "{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}");
	while (index) {
		unsigned int next = index->next_sibling ? index->next_sibling->index : 0;
		unsigned int child = index->first_child ? index->first_child->index : 0;
		char key = index->key;
		fprintf(fptr, "\n,{.key = '%C', .next_sibling = %u, .first_child = %u, .termination_code = %s}", key, next, child, (index->termination_code ? index->termination_code : "0"));
		// std::cout << ",\n" << "{.key = '" << key << "', .next_sibling = " << next << ", .first_child = " << child << ", .termination_code = " << termination_code << "}";
		index = index->index_route;
	}
	fprintf(fptr, "};\n");
}


//---------------------------------------------------
// Helpers
//---------------------------------------------------


unsigned int log2(unsigned int v) {
	if (v < 2) return 1;
	if (v < 4) return 2;
	if (v < 8) return 3;
	if (v < 16) return 4;
	if (v < 32) return 5;
	if (v < 64) return 6;
	if (v < 128) return 7;
	if (v < 256) return 8;
	if (v < 512) return 9;
	if (v < 1024) return 10;
	if (v < 2048) return 11;
	if (v < 4096) return 12;
	return 13;
}