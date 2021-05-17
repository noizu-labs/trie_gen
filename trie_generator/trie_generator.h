/*!
* @file trie_generator.h
*
* @author Keith Brings
* @repo github.com/noizu/trie_gen
* @copyright Noizu Labs, Inc. 2021.
*/

#ifndef __TRIE_GENERATOR_H__
#define __TRIE_GENERATOR_H__

#define TRUE 1
#define FALSE 0

/*!
 * @brief linked list for tracking node_index->token entries under compact encoding.
 */
typedef struct noizu_auto_trie_compact_token_node {
	unsigned int node_index;
	char* token;
	struct noizu_auto_trie_compact_token_node* next;
} noizu_auto_trie_compact_token_node;

/*!
 * @breif book keeping details for preparing compact encoded trie output.
 */
typedef struct noizu_auto_trie_compact_details {
	unsigned char char_reverse[256];
	unsigned char char_map[256];
	unsigned char char_count;
	unsigned largest_sibling_jump;
	unsigned largest_child_jump;

	unsigned int node_count;
	unsigned int token_count;
	noizu_auto_trie_compact_token_node* token_map;
	noizu_auto_trie_compact_token_node* token_map_tail;
} noizu_auto_trie_compact_details;

/*!
 * @brief Simple trie for dynamically building structure before writting static version to file.
 */
typedef struct noizu_auto_trie_node {
	char key;

	unsigned int index;
	struct noizu_auto_trie_node* index_route;

	unsigned int relative_sibling_index;
	unsigned int relative_child_index;

	struct noizu_auto_trie_node* next_sibling;
	struct noizu_auto_trie_node* first_child;
	char* termination_code;
} NoizuAutoTrie;




//---------------------------------------------------
// Trie Transversal & Construction
//---------------------------------------------------

/*!
 * @brief add string to trie.
 */
void insert(char* token, char* termination_code, NoizuAutoTrie* root);

/*!
 * @brief obtain trie child (if any) for input character.
 */
NoizuAutoTrie* child(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie child (if any) for input character or insert.
 */
NoizuAutoTrie* obtain_child(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie sibling (if any) for input character.
 */
NoizuAutoTrie* sibling(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie sibling (if any) for input character or insert.
 */
NoizuAutoTrie* obtain_sibling(char k, NoizuAutoTrie* parent);

/*!
 * @brief walk to next position in trie given input character.
 */
NoizuAutoTrie* advance(char k, NoizuAutoTrie* position);


//---------------------------------------------------
// Data Prep needed for output.
//---------------------------------------------------
/*!
 * @breif Enumerate trie nodes for output list.
 */
NoizuAutoTrie* gen_prep(NoizuAutoTrie* root);

/*!
 *  @brief prepare supporting structures required for compact format output.
 */
void gen_prep_details(NoizuAutoTrie* n, noizu_auto_trie_compact_details* details);

/*!
 * @brief Prep node siblings for code generation (track indexes)
 */
NoizuAutoTrie* gen_prep_siblings(NoizuAutoTrie* n, NoizuAutoTrie* index);

/*!
 * @brief Prep node childrens for code generation (track indexes)
 */
NoizuAutoTrie* gen_prep_children(NoizuAutoTrie* n, NoizuAutoTrie* index);

/*!
 * @brief Prep node siblings for code generation (track indexes)
 */
NoizuAutoTrie* gen_prep_siblings_depth_first(NoizuAutoTrie* n, NoizuAutoTrie* index);

/*!
 * @brief Prep node childrens for code generation (track indexes)
 */
NoizuAutoTrie* gen_prep_children_depth_first(NoizuAutoTrie* n, NoizuAutoTrie* index);

NoizuAutoTrie* gen_prep_depth_first(NoizuAutoTrie* root);


//---------------------------------------------------
// Generate
//---------------------------------------------------

/*!
 * @brief Generate code for array or int encoded static trie.
 */
void gen_array_format(char* genVar, NoizuAutoTrie* index, FILE* fptr);

/*!
 * @brief Generate code for array of struct encoded static trie.
 */
void gen_struct_format(char* genVar, NoizuAutoTrie* index, FILE* fptr);

/*!
 * @brief Generate compact format trie.
 */
void gen_compact_format(char* genVar, NoizuAutoTrie* index, noizu_auto_trie_compact_details* details, FILE* fptr);

//---------------------------------------------------
// Helpers
//---------------------------------------------------

/*!
 * return number of bits needed to encode values between zero and input
 */
unsigned int log2(unsigned int v);

#endif