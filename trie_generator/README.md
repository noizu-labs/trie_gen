Noizu Trie Generator
==========================================

The Noizu Trie Generator may be used to create compile time trie lookup table, using either a user friendly array of structs or barebones array or int implementation. 

Generator your Trie, copy and paste the generated output into your project and include the noizu_trie.c and noizu_trie.h files in your project path.


```
typedef int NoizuMicroTrie[4];

// Example 
trie_generator.exe sample.text import/generated.gen my_trie

// Input
DEF_VAR_1|Token One
DEF_VAR_2|Another Token
1234|Token Three Hundred
4312|More Tokens

// Output
NoizuMicroTrie my_trie[] = {{0, 0, 0, 0}
,{'*', 0, 2, 0}
,{'A', 3, 36, 0}
,{'M', 4, 5, 0}
,{'T', 0, 15, 0}
,{'o', 0, 6, 0}
,{'r', 0, 7, 0}
,{'e', 0, 8, 0}
,{' ', 0, 9, 0}
,{'T', 0, 10, 0}
,{'o', 0, 11, 0}
,{'k', 0, 12, 0}
,{'e', 0, 13, 0}
,{'n', 0, 14, 0}
,{'s', 0, 0, 4312}
,{'o', 0, 16, 0}
,{'k', 0, 17, 0}
,{'e', 0, 18, 0}
,{'n', 0, 19, 0}
,{' ', 0, 20, 0}
,{'O', 21, 34, 0}
,{'T', 0, 22, 0}
,{'h', 0, 23, 0}
,{'r', 0, 24, 0}
,{'e', 0, 25, 0}
,{'e', 0, 26, 0}
,{' ', 0, 27, 0}
,{'H', 0, 28, 0}
,{'u', 0, 29, 0}
,{'n', 0, 30, 0}
,{'d', 0, 31, 0}
,{'r', 0, 32, 0}
,{'e', 0, 33, 0}
,{'d', 0, 0, 1234}
,{'n', 0, 35, 0}
,{'e', 0, 0, DEF_VAR_1}
,{'n', 0, 37, 0}
,{'o', 0, 38, 0}
,{'t', 0, 39, 0}
,{'h', 0, 40, 0}
,{'e', 0, 41, 0}
,{'r', 0, 42, 0}
,{' ', 0, 43, 0}
,{'T', 0, 44, 0}
,{'o', 0, 45, 0}
,{'k', 0, 46, 0}
,{'e', 0, 47, 0}
,{'n', 0, 0, DEF_VAR_2}};



```


```
typedef struct noizu_static_trie {
	char key;
	unsigned int next_sibling;
	unsigned int first_child;
	unsigned int termination_code;
} NoizuStaticTrie;


// Example 
trie_generator.exe sample.text import/generated.gen my_trie struct

// Input
DEF_VAR_1|Token One
DEF_VAR_2|Another Token
1234|Token Three Hundred
4312|More Tokens


NoizuStaticTrie forecast_trie[] = {{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}
,{.key = '*', .next_sibling = 0, .first_child = 2, .termination_code = 0}
,{.key = 'A', .next_sibling = 3, .first_child = 36, .termination_code = 0}
,{.key = 'M', .next_sibling = 4, .first_child = 5, .termination_code = 0}
,{.key = 'T', .next_sibling = 0, .first_child = 15, .termination_code = 0}
,{.key = 'o', .next_sibling = 0, .first_child = 6, .termination_code = 0}
,{.key = 'r', .next_sibling = 0, .first_child = 7, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 8, .termination_code = 0}
,{.key = ' ', .next_sibling = 0, .first_child = 9, .termination_code = 0}
,{.key = 'T', .next_sibling = 0, .first_child = 10, .termination_code = 0}
,{.key = 'o', .next_sibling = 0, .first_child = 11, .termination_code = 0}
,{.key = 'k', .next_sibling = 0, .first_child = 12, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 13, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 14, .termination_code = 0}
,{.key = 's', .next_sibling = 0, .first_child = 0, .termination_code = 4312}
,{.key = 'o', .next_sibling = 0, .first_child = 16, .termination_code = 0}
,{.key = 'k', .next_sibling = 0, .first_child = 17, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 18, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 19, .termination_code = 0}
,{.key = ' ', .next_sibling = 0, .first_child = 20, .termination_code = 0}
,{.key = 'O', .next_sibling = 21, .first_child = 34, .termination_code = 0}
,{.key = 'T', .next_sibling = 0, .first_child = 22, .termination_code = 0}
,{.key = 'h', .next_sibling = 0, .first_child = 23, .termination_code = 0}
,{.key = 'r', .next_sibling = 0, .first_child = 24, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 25, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 26, .termination_code = 0}
,{.key = ' ', .next_sibling = 0, .first_child = 27, .termination_code = 0}
,{.key = 'H', .next_sibling = 0, .first_child = 28, .termination_code = 0}
,{.key = 'u', .next_sibling = 0, .first_child = 29, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 30, .termination_code = 0}
,{.key = 'd', .next_sibling = 0, .first_child = 31, .termination_code = 0}
,{.key = 'r', .next_sibling = 0, .first_child = 32, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 33, .termination_code = 0}
,{.key = 'd', .next_sibling = 0, .first_child = 0, .termination_code = 1234}
,{.key = 'n', .next_sibling = 0, .first_child = 35, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 0, .termination_code = DEF_VAR_1}
,{.key = 'n', .next_sibling = 0, .first_child = 37, .termination_code = 0}
,{.key = 'o', .next_sibling = 0, .first_child = 38, .termination_code = 0}
,{.key = 't', .next_sibling = 0, .first_child = 39, .termination_code = 0}
,{.key = 'h', .next_sibling = 0, .first_child = 40, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 41, .termination_code = 0}
,{.key = 'r', .next_sibling = 0, .first_child = 42, .termination_code = 0}
,{.key = ' ', .next_sibling = 0, .first_child = 43, .termination_code = 0}
,{.key = 'T', .next_sibling = 0, .first_child = 44, .termination_code = 0}
,{.key = 'o', .next_sibling = 0, .first_child = 45, .termination_code = 0}
,{.key = 'k', .next_sibling = 0, .first_child = 46, .termination_code = 0}
,{.key = 'e', .next_sibling = 0, .first_child = 47, .termination_code = 0}
,{.key = 'n', .next_sibling = 0, .first_child = 0, .termination_code = DEF_VAR_2}};
```