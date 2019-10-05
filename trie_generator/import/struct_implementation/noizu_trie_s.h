/*!
* @file noizu_trie_s.h
* @brief structed encoded static trie implementation.
*
* @author Keith Brings
* @copyright Noizu Labs, Inc. 2019.
*/

#ifndef __NOIZU_TRIE_S_H__
#define __NOIZU_TRIE_S_H__

#ifndef TRIE_NOT_FOUND
/*!
 * @brief string not found special index value.
 * This special trie index functions as termination well to halt processing of non matched input strings.
 * In generated tries trie head begin at index position (1) with a non parsed special token value. (*) by default.
 */
#define TRIE_NOT_FOUND 0
#endif

#ifndef TRIE_S_UNIT
 /*!
  * @brief string not found special index value.
  * This special trie index functions as termination well to halt processing of non matched input strings.
  * In generated tries trie head begin at index position (1) with a non parsed special token value. (*) by default.
  */
#define TRIE_S_UNIT unsigned int
#endif

#ifndef TRIE_S_TOKEN
#define TRIE_S_TOKEN unsigned int
#endif

/*!
 * @brief trie node structure. Static trie encoded as an array of structs or pointer to allocation of structs.
 */
typedef struct noizu_trie_s{
	char key;
	TRIE_S_UNIT next_sibling;
	TRIE_S_UNIT first_child;
	TRIE_S_TOKEN termination_code;
} noizu_trie_s;

/*!
 * @brief advance position through trie structure by find sibling or direct child matching index node. Return TRIE_NOT_FOUND indicator if current node not found or matching entry exists.
 */
TRIE_S_UNIT noizu_trie_s_advance(char k, TRIE_S_UNIT current_node, noizu_trie_s* source);

#endif
