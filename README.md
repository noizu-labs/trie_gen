Noizu Trie Generator
==========================================

The Noizu Trie Generator may be used to create compile time trie lookup table, using either a user friendly array of structs or barebones array or int (or char) implementation.
Generate your Trie, copy and paste the generated output into your project and include the noizu_trie.c and noizu_trie.h files in your project path.

Use in combination with the [Noizu Streaming Json](http://github.com/noizu/streaming-json-parser) for fast compact parsing of too large for memory embedded data streams.

# To Use
Use executable to generate code.
`trie_generator.exe input.txt [output.file|import/generated.gen] [name|trie] [mode|(min|struct)]`

input.txt - file to extract trie from.
output.file - output file for generated trie
name - name of generated trie variable.
mode - array of int or array of struct encoded trie.

Include appropriate noizu_trie_a.h and noizu_trie_a.c or noizu_trie_s.h, noizu_trie_s.c in your applications include path.

# Examples

## Array Implementation
```
typedef int noizu_trie_a[4];

// Example
trie_generator.exe sample.text import/generated.gen my_trie

// Input  (Macro Def, Enum or Integer Identifier for Input String)
DEF_VAR_1|Token One
DEF_VAR_2|Another Token
1234|Token Three Hundred
4312|More Tokens

// Output
noizu_trie_a my_trie[] = {{0, 0, 0, 0}
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


## Struct Implementation
```
typedef struct noizu_trie_s {
	char key;
	unsigned int next_sibling;
	unsigned int first_child;
	unsigned int termination_code;
} noizu_trie_s;


// Example
trie_generator.exe sample.text import/generated.gen my_trie struct

// Input
DEF_VAR_1|Token One
DEF_VAR_2|Another Token
1234|Token Three Hundred
4312|More Tokens


noizu_trie_s forecast_trie[] = {{.key = 0, .next_sibling = 0, .first_child = 0, .termination_code = 0}
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


##  Bit packed implementation
```
// _my_trie: CharMap
TRIE_C_CHAR _my_trie_cm(TRIE_C_CHAR c) {
    if (c == '*') return 1;
    if (c == 'A') return 2;
    if (c == 'n') return 3;
    if (c == 'o') return 4;
    if (c == 't') return 5;
    if (c == 'h') return 6;
    if (c == 'e') return 7;
    if (c == 'r') return 8;
    if (c == ' ') return 9;
    if (c == 'T') return 10;
    if (c == 'k') return 11;
    if (c == 'M') return 12;
    if (c == 's') return 13;
    if (c == 'O') return 14;
    if (c == 'H') return 15;
    if (c == 'u') return 16;
    if (c == 'd') return 17;
    return 0;
}

TRIE_C_CHAR _my_trie_chars[] = {'*', 'A', 'n', 'o', 't', 'h', 'e', 'r', ' ', 'T', 'k', 'M', 's', 'O', 'H', 'u', 'd'};

// _my_trie: SetToken
TRIE_C_TOKEN _my_trie_token(TRIE_C_TOKEN clear, noizu_trie_compact_state* state, noizu_trie_compact_definition* definition) {
    TRIE_C_TOKEN has_token = 1;
    TRIE_C_TOKEN token = 0;
    TRIE_C_UNIT index = state->trie_index;
    if (index == 13) token = DEF_VAR_2;
    else if (index == 24) token = 4312;
    else if (index == 33) token = DEF_VAR_1;
    else if (index == 46) token = 1234;
    else has_token = 0;

    if (((clear && !has_token) || has_token) && state->token != TRIE_NOT_FOUND) {
        state->last_token = state->token;
        state->last_token_index == state->token_index;
    }
    if (clear && !has_token) {
        state->token = 0;
        state->token_index = 0;
    }
    if (clear && !has_token) {
        state->token = 0;
        state->token_index = 0;
    }
    if (has_token) {
    state->token = token;
    state->token_index = state->trie_index;
    }
    return (has_token ? TRIE_PARTIAL_MATCH : TRIE_NOT_FOUND);
}



// _my_trie: Node Binary| Bits per field = 10, required = 59
unsigned char _my_trie_node_map[] = {
0X08,0X45,0XB1,0X84,
0X81,0X28,0X4C,0X13,
0X85,0X01,0X48,0X54,
0X12,0X05,0X61,0X38,
0X46,0X06,0X5C,0X81,
0X40,0X4E,0X14,0X85,
0X41,0X20,0X56,0X13,
0X84,0X61,0X68,0X14,
0X12,0X05,0X61,0X38,
0X46,0X14,0X85,0XC7,
0X18,0X4E,0X05,0X04,
0XC1,0X40,0X4E,0X13,
0X85,0X21,0X78,0X60,
0X11,0X86,0X21,0X40,
0X4E,0X18,0X80,};


// _my_trie: Compact Trie Definition, max_sibling_jump=13 rows
noizu_trie_compact_definition _my_trie = {
    .size = 47,
    .tokens = 4,
    .characters = 17,
    .bit_length__character_code = 5,
    .bit_length__sibling_relative_index = 4,
    .bit_length__child_relative_index = 1,
    .bit_length__child_relative_offset = 9,
    .bit_length = 10,
    .trie_raw = _my_trie_node_map,
    .trie_raw_length = 59,
    .char_map = _my_trie_chars,
    .set_node_token = _my_trie_token,
    .char_code = _my_trie_cm
};


```
