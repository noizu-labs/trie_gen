#ifndef __NOIZU_TRIE_H__
#define __NOIZU_TRIE_H__


typedef int NoizuMicroTrie[4];

typedef struct noizu_static_trie {
	char key;
	unsigned int next_sibling;
	unsigned int first_child;
	unsigned int termination_code;
} NoizuStaticTrie;

unsigned int advance(char key, unsigned int position, NoizuStaticTrie* source);
unsigned int mt_advance(char key, unsigned int position, NoizuMicroTrie source[]);




#endif
