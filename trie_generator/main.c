#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*!
 * @brief Simple trie for dynamically building structure before writting static version to file. 
 */
typedef struct noizu_auto_trie_node {
	char key;

	unsigned int index;
	struct noizu_auto_trie_node* index_route;

	struct noizu_auto_trie_node* next_sibling;
	struct noizu_auto_trie_node* first_child;
	char* termination_code;
} NoizuAutoTrie;

/*!
 * @breif Setup for array encoded trie output
 */
NoizuAutoTrie* gen_prep(NoizuAutoTrie* root);

/*!
 * @brief Prep node siblings for code generation (track indexes) 
 */
NoizuAutoTrie* gen_prep_siblings(NoizuAutoTrie* n, NoizuAutoTrie* index);

/*!
 * @brief Prep node childrens for code generation (track indexes)
 */
NoizuAutoTrie* gen_prep_children(NoizuAutoTrie* n, NoizuAutoTrie* index);

/*!
 * @brief Generate code for array or int encoded static trie.
 */
void gen(char* genVar, NoizuAutoTrie* index, FILE *fptr);
/*!
 * @brief Generate code for array of struct encoded static trie.
 */
void gen_struct(char* genVar, NoizuAutoTrie* index, FILE* fptr);

/*!
 * @brief add string to trie.
 */
static void insert(char* token, char* termination_code, NoizuAutoTrie* root);

/*!
 * @brief obtain trie child (if any) for input character.
 */
static NoizuAutoTrie* child(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie child (if any) for input character or insert.
 */
static NoizuAutoTrie* obtain_child(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie sibling (if any) for input character.
 */
static NoizuAutoTrie* sibling(char k, NoizuAutoTrie* parent);

/*!
 * @brief obtain trie sibling (if any) for input character or insert.
 */
static NoizuAutoTrie* obtain_sibling(char k, NoizuAutoTrie* parent);

/*!
 * @brief walk to next position in trie given input character.
 */
static NoizuAutoTrie* advance(char k, NoizuAutoTrie* position);

void gen(char* genVar, NoizuAutoTrie* index, FILE *fptr) {
	fprintf(fptr, "\n\n#include \"noizu_trie_a.h\"\n\nnoizu_trie_a %s[] = {", genVar);
	fprintf(fptr, "{0, 0, 0, 0}");
	while (index) {
		unsigned int next = index->next_sibling ? index->next_sibling->index : 0;
		unsigned int child = index->first_child ? index->first_child->index : 0;
		char key = index->key;
		fprintf(fptr, ",\n{'%C', %u, %u, %s}", key, next, child, (index->termination_code ? index->termination_code : "0"));
		// std::cout << ",\n" << "{.key = '" << key << "', .next_sibling = " << next << ", .first_child = " << child << ", .termination_code = " << termination_code << "}";
		index = index->index_route;
	}
	fprintf(fptr, "};\n");
}

void gen_struct(char* genVar, NoizuAutoTrie* index, FILE* fptr) {
	fprintf(fptr, "\n\n#include \"noizu_trie_s.h\"\n\noizu_trie_s %s[] = {", genVar);
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
		if (p->termination_code) {
			printf("Error| Path Already Set %s, %s\n", token, p->termination_code);
		}
		//printf("Termination Code = %s, %d\n", termination_code, strlen(termination_code));
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
#ifdef PROOF_OF_CONCEPT
	t();
#endif
	printf("ARGC = %d, %s\n", argc, argv[0]);

	printf("\n\nARGV2 = %s\n", argv[2]);

	if (argc < 2) {
		printf("Usage: trie_generator.exe input.txt [output.file|import/generated.gen] [name|trie] [mode|(min|struct)]");
		return 1;
	}
	
	// Setup User Arguments
	char* inputFile = argv[1];
	char defaultOutputFile[] = "import/generated.gen";
	char* outputFile = (argc > 2) ? argv[2] : &defaultOutputFile;
	char defaultOutputVar[] = "noizu_trie";
	char* outputVar = (argc > 3) ? argv[3] : &defaultOutputFile;
	int structMode = 0;

	if (argc > 4) {
		structMode = (strncmp(argv[4], "struct", 6) == 0) ? 1 : 0;
	}

	// Setup Root Node
	NoizuAutoTrie* root = (NoizuAutoTrie*)malloc(sizeof(NoizuAutoTrie));	
	if (root) {
		memset(root, 0, sizeof(NoizuAutoTrie));
		root->key = '*';
	}
	else {
		printf("[Error] Malloc Fail Line:%d", __LINE__);
		return 1;
	}
	
	// Parse Input File
	printf("------------------[Noizu Trie Gen: %d]---------------------\n", argc);
	printf("Input File: %s\n", inputFile);
	printf("Output File: %s\n", outputFile);
	printf("Output Name: %s\n", outputVar);
	printf("Trie Type: %s\n", structMode ? "NoizuStaticTrie" : "NoizuMicroTrie");
	printf("-------------------------------------------------------\n");

	FILE *fptr;
	errno_t err;
	err = fopen_s(&fptr, inputFile, "r");
	if (!err && fptr) {		
		char line[2048] = { 0 };
		int pos = 0;
		// grab line, since getline isn't handy on windows. 
		char c = 0;
		while (TRUE) {
			pos = 0;
			while ((c = fgetc(fptr)) != EOF) {
				line[pos] = c;
				if (c == '\n' || c == '\r') {
					break;
				}
				pos++;
			}
			line[pos] = '\0';
			//printf("Line: %s\n", line);
			char token[255];
			char code[255];
			if (sscanf_s(line, "%[^|\n\r ]|%[^\n\r]", code, 255, token, 255) == 2) {
				insert(token, code, root);
			}

			if (c == EOF) break;			
		}
		
		err = fopen_s(&fptr, outputFile, "w");
		if (!err && fptr) {
			gen_prep(root);
			if (structMode) {
				gen_struct(outputVar, root, fptr);
			}
			else {
				gen(outputVar, root, fptr);
			}			
			fclose(fptr);
			printf("\n\n[Complete]\n\n\n", outputFile);
			return 0;
		}
		else {
			printf("\n\n[Error] - Openning Output File %s", outputFile);
			return 2;
		}
	}
	else {
		printf("\n\n[Error] - Opening Input File %s", inputFile);
		return 3;
	}	
}



