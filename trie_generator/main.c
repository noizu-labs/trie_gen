#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct noizu_auto_trie_node {
	char key;

	unsigned int index;
	struct noizu_auto_trie_node* index_route;

	struct noizu_auto_trie_node* next_sibling;
	struct noizu_auto_trie_node* first_child;
	char* termination_code;
} NoizuAutoTrie;

NoizuAutoTrie* gen_prep(NoizuAutoTrie* root);
NoizuAutoTrie* gen_prep_siblings(NoizuAutoTrie* n, NoizuAutoTrie* index);
NoizuAutoTrie* gen_prep_children(NoizuAutoTrie* n, NoizuAutoTrie* index);
void gen(NoizuAutoTrie* index, FILE *fptr);

static void insert(char* token, char* termination_code, NoizuAutoTrie* root);
static NoizuAutoTrie* child(char k, NoizuAutoTrie* parent);
static NoizuAutoTrie* obtain_child(char k, NoizuAutoTrie* parent);
static NoizuAutoTrie* sibling(char k, NoizuAutoTrie* parent);
static NoizuAutoTrie* obtain_sibling(char k, NoizuAutoTrie* parent);
static NoizuAutoTrie* advance(char k, NoizuAutoTrie* position);

void gen(NoizuAutoTrie* index, FILE *fptr) {
	// @todo should be outputting to a stream. 
	
	// 1. 0 null indicator entry. 
	// std::cout << "{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}";
	fprintf(fptr, "{0, 0, 0, 0}");
	while (index) {
		unsigned int next = index->next_sibling ? index->next_sibling->index : 0;
		unsigned int child = index->first_child ? index->first_child->index : 0;
		char key = index->key;
		fprintf(fptr, "\n,{'%C', %u, %u, %s}", key, next, child, (index->termination_code ? index->termination_code : "0"));
		// std::cout << ",\n" << "{.key = '" << key << "', .next_sibling = " << next << ", .first_child = " << child << ", .termination_code = " << termination_code << "}";
		index = index->index_route;
	}
}

void gen_struct(NoizuAutoTrie* index, FILE* fptr) {
	// @todo should be outputting to a stream. 

	// 1. 0 null indicator entry. 
	// std::cout << "{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}";
	fprintf(fptr, "{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}");
	while (index) {
		unsigned int next = index->next_sibling ? index->next_sibling->index : 0;
		unsigned int child = index->first_child ? index->first_child->index : 0;
		char key = index->key;
		fprintf(fptr, "\n,{.key = '%C', .next_sibling = %u, .first_child = %u, .termination_code = %s}", key, next, child, (index->termination_code ? index->termination_code : "0"));
		// std::cout << ",\n" << "{.key = '" << key << "', .next_sibling = " << next << ", .first_child = " << child << ", .termination_code = " << termination_code << "}";
		index = index->index_route;
	}
}



NoizuAutoTrie* gen_prep(NoizuAutoTrie* root) {
	// std::cout << "gen_prep" << "\n";
	NoizuAutoTrie* p = root;
	p->index = 1;
	p = gen_prep_siblings(root, p);
	p = gen_prep_children(root, p);
	return p;
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

static void insert(char* token, char * termination_code, NoizuAutoTrie* root) {
	NoizuAutoTrie* p = root;
	while (*token != '\0') {
		p = obtain_child(*token, p);
		token++;
	}

	if (p) {
		printf("Termination Code = %s, %d\n", termination_code, strlen(termination_code));
		p->termination_code = (char*) malloc((strlen(termination_code) + 1));
		strcpy_s(p->termination_code, strlen(termination_code) + 1, termination_code);
	}
}

static NoizuAutoTrie* child(char k, NoizuAutoTrie* parent) {
	if (parent->first_child) {
		return sibling(k, parent);
	}
	else {
		return NULL;
	}
}

static NoizuAutoTrie* obtain_child(char k, NoizuAutoTrie* parent) {
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

static NoizuAutoTrie* sibling(char k, NoizuAutoTrie* parent) {	
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

static NoizuAutoTrie* obtain_sibling(char k, NoizuAutoTrie* parent) {
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
		parent->first_child = (NoizuAutoTrie*) malloc(sizeof(NoizuAutoTrie));		
		if (parent->first_child) {
			memset(parent->first_child, 0, sizeof(NoizuAutoTrie));
		}
		parent->first_child->key = k;
		return parent->first_child;
	}
}

static NoizuAutoTrie* advance(char k, NoizuAutoTrie* position) {
	if (position) {
		return child(k, position);
	}
	else {
		return NULL;
	}
}


int main(int argc, char *argv[])
{
	NoizuAutoTrie* root = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));	
	if (root) {
		memset(root, 0, sizeof(NoizuAutoTrie));
	}
	root->key = '*';

	char trieName[] = "generated";
	char trieFile[] = "import/generated.gen";
	char inputFile[] = "sample.txt";

	FILE *fptr;
	errno_t err;
	err = fopen_s(&fptr, inputFile, "r");
	if (!err) {		
		char line[2048] = { 0 };
		int pos = 0;
		// grab line, since getline isn't handy on windows. 
		char c = 0;
		while (TRUE) {
			while (c = fgetc(fptr)) {
				if (c == EOF) break;
				line[pos] = c;
				if (c == '\n') {					
					break;
				}
				pos++;
			}
			line[pos] = '\0';

			char token[255];
			char code[255];
			if (sscanf_s(line, "%[^|]|%[^\n\r]", code, 255, token, 255) == 2) {
				//printf("Debugging: %s, %s = %s\n", line, code, token);				
				insert(token, code, root);
			}

			pos = 0;
			if (c == EOF) {
				break;
			}
		}
		
		err = fopen_s(&fptr, trieFile, "w");
		if (!err) {
			//fprintf(fptr, "\n\n#include \"noizu_auto_trie.h\"\n\nNoizuStaticTrie %s[] = {", trieName);
			fprintf(fptr, "\n\n#include \"noizu_auto_trie.h\"\n\nNoizuMicroTrie %s[] = {", trieName);
			gen_prep(root);
			gen(root, fptr);
			fprintf(fptr, "};\n");
			fclose(fptr);
			printf("[Complete]");
		}
		else {
			printf("[Error]");
		}
	}
	else {
		printf("[Error]");
	}


	
#ifdef PROOF_OF_CONCEPT
	t();
#endif
	return 0;
}



