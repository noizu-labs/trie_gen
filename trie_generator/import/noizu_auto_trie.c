#include "noizu_auto_trie.h"

static unsigned int child(char k, unsigned int parent, NoizuStaticTrie* source);

unsigned int advance(char key, unsigned int position, NoizuStaticTrie* source) {
	if (position == 0) {
		return 0;
	}
	return child(key, position, source);
}

static unsigned int child(char k, unsigned int parent, NoizuStaticTrie* source) {
	if (parent == 0) return 0;
	unsigned int p = (*(source + parent)).first_child;
	while (p) {
		if ((*(source + p)).key == k) {
			return p;
		}
		
		if ((*(source + p)).key < k) {
			p = (*(source + p)).next_sibling;
		}
	}
	return 0;
}



int mt_child(char key, int parent, NoizuMicroTrie source[]) {
	if (parent == 0) return 0;

	int p = source[parent][2];
	printf("%d: p = %d", __LINE__, p);
	while (p) {
		printf("%d: (%d) source[p][0] = %d\n", __LINE__, p, source[p][0]);
		if (source[p][0] == key) {
			printf("return");
			return p;
		}
		if (source[p][0] < key) {
			printf("next sibling = %d", source[p][1]);
			p = source[p][1];
		}
	}
	return 0;
}

int mt_advance(char key, int position, NoizuMicroTrie source[]) {
	if (position == 0) return 0;
	return mt_child(key, position, source);
}

#ifdef PROOF_OF_CONCEPT 
// Proof of Concept

NoizuMicroTrie generated[] = { {0, 0, 0, 0}
,{'*', 0, 2, 0}
,{'T', 0, 3, 0}
,{'o', 0, 4, 0}
,{'k', 0, 5, 0}
,{'e', 0, 6, 0}
,{'n', 0, 7, 0}
,{' ', 8, 10, 0}
,{'2', 9, 0, 5412}
,{'3', 0, 0, 5321}
,{'W', 0, 11, 0}
,{'i', 0, 12, 0}
,{'t', 0, 13, 0}
,{'h', 0, 14, 0}
,{' ', 0, 15, 0}
,{'S', 0, 16, 0}
,{'p', 0, 17, 0}
,{'a', 0, 18, 0}
,{'c', 0, 19, 0}
,{'e', 0, 20, 0}
,{'s', 0, 0, 1234} };


void t() {
	printf("\nRun Test\n");
	int p = 1;
	p = mt_advance('T', p, generated);

	p = mt_advance('o', p, generated);
	p = mt_advance('k', p, generated);
	p = mt_advance('e', p, generated);
	p = mt_advance('n', p, generated);
	p = mt_advance(' ', p, generated);
	p = mt_advance('W', p, generated);
	p = mt_advance('i', p, generated);
	p = mt_advance('t', p, generated);
	p = mt_advance('h', p, generated);
	p = mt_advance(' ', p, generated);
	p = mt_advance('S', p, generated);
	p = mt_advance('p', p, generated);
	p = mt_advance('a', p, generated);
	p = mt_advance('c', p, generated);
	p = mt_advance('e', p, generated);
	p = mt_advance('s', p, generated);
	printf("Test %d, %d", p, generated[p][3]);
}

#endif