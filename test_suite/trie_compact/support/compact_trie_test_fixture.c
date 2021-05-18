#include "trie_test_fixture.h"


// compact_test_trie: CharMap
TRIE_CHAR_CODE __internal_compact_test_trie_cm(TRIE_CHAR_CODE c) {
    if (c == '*') return 1;
    if (c == 'c') return 2;
    if (c == 'o') return 3;
    if (c == 'n') return 4;
    if (c == 't') return 5;
    if (c == 'e') return 6;
    if (c == 's') return 7;
    if (c == 'd') return 8;
    if (c == 'g') return 9;
    if (c == 'r') return 10;
    if (c == '_') return 11;
    if (c == 'l') return 12;
    if (c == 'i') return 13;
    if (c == 'u') return 14;
    if (c == 'a') return 15;
    if (c == 'b') return 16;
    if (c == 'f') return 17;
    if (c == 'h') return 18;
    if (c == '+') return 19;
    if (c == 'p') return 20;
    if (c == 'v') return 21;
    if (c == 'm') return 22;
    if (c == 'y') return 23;
    if (c == 'w') return 24;
    return 0;
}

TRIE_CHAR_CODE __internal_compact_test_trie_chars[] = { '*', 'c', 'o', 'n', 't', 'e', 's', 'd', 'g', 'r', '_', 'l', 'i', 'u', 'a', 'b', 'f', 'h', '+', 'p', 'v', 'm', 'y', 'w' };

// compact_test_trie: GetToken
TRIE_TOKEN __internal_compact_test_trie_token(uint32_t index, noizu_trie_definition* definition, uint8_t* has_token) {
    *has_token = 1;
    TRIE_TOKEN token = 0;

    if (index == 8) token = COMPACT_JK_CONTENTS;
    else if (index == 23) token = COMPACT_JV_DEGREES_CELSIUS;
    else if (index == 32) token = COMPACT_JV_DEGREES_CELSIUS_CONTENTS;
    else if (index == 39) token = COMPACT_JK_ENABLED;
    else if (index == 47) token = COMPACT_JK_FEATURED;
    else if (index == 52) token = COMPACT_JK_FIELDS;
    else if (index == 57) token = COMPACT_HELLO;
    else if (index == 63) token = COMPACT_HELLO_HELLO;
    else if (index == 66) token = COMPACT_JK_ONE;
    else if (index == 72) token = COMPACT_JK_OPTIONS;
    else if (index == 89) token = COMPACT_JV_RELATIVE_HUMIDITY;
    else if (index == 94) token = COMPACT_JK_THREE;
    else if (index == 96) token = COMPACT_JK_TWO;
    else *has_token = 0;

    return token;
}



// compact_test_trie: Node Binary| Bits per field = 11, required = 134
unsigned char __internal_compact_test_trie_node_map[] = {
0X08,0X22,0X44,0X60,
0X90,0X12,0X82,0X60,
0X48,0X09,0X41,0X38,
0X08,0XC4,0XC0,0XA4,
0X15,0X02,0X60,0X4C,
0X09,0XC1,0X58,0X22,
0X04,0XC0,0XB0,0X13,
0X82,0XD0,0X5C,0X09,
0XC1,0X58,0X22,0X04,
0X60,0X90,0X12,0X82,
0X60,0X48,0X09,0X41,
0X38,0X06,0X3C,0X80,
0XBC,0X18,0X02,0XC0,
0X4C,0X0A,0000,0X8B,
0X66,0X3D,0XE0,0X94,
0X17,0X02,0XA0,0X4C,
0X0A,0000,0X68,0X26,
0X05,0X80,0XA0,0X13,
0X81,0X25,0XCC,0X0B,
0X01,0X60,0X23,0X06,
0X60,0XC8,0X13,0X02,
0XC0,0X58,0X08,0XC0,
0X1A,0X64,0X14,0XC0,
0X50,0X12,0X82,0XD0,
0X46,0X09,0X01,0X38,
0X0A,0X8C,0XC0,0XB0,
0X17,0X82,0X50,0X5A,
0X0D,0X41,0X30,0X2B,
0X06,0X40,0XB8,0X1B,
0X02,0XD0,0X50,0X0B,
0X41,0X28,0X37,0000,
0XA0,0XC8,0X95,0X02,
0X60,0X4C,0X06,0X01,
0X18,0000, };


// compact_test_trie: Compact Trie Definition, max_sibling_jump=24 rows
struct noizu_trie__compact__definition compact_test_trie_inner_def = {
    .size = 97,
    .tokens = 13,
    .characters = 24,
    .bit_length__character_code = 5,
    .bit_length__sibling_relative_index = 5,
    .bit_length__child_relative_index = 1,
    .bit_length__child_relative_offset = 10,
    .bit_length = 11,
    .trie_raw = __internal_compact_test_trie_node_map,
    .trie_raw_length = 134,
    .char_map = __internal_compact_test_trie_chars,
    .token_code = __internal_compact_test_trie_token,
    .char_code = __internal_compact_test_trie_cm
};
struct noizu_trie_definition compact_test_trie = {
    .constant = 1,
    .type = TRIE_COMPACT_TYPE,
    .type_definition = &compact_test_trie_inner_def,
    .trie_init = noizu_trie__compact__init,
    .trie_free = noizu_trie__compact__free,
    .trie_validate = noizu_trie__compact__validate,
    .trie_advance = noizu_trie__compact__advance,
    .trie_tokenize = NULL
};