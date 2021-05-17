#include "unity.h"
#include "unity_fixture.h"

#include "noizu_trie.h"
#include "noizu_trie_c.h"


TEST_GROUP(TrieCompact);

#define COMPACT_JK_FIELDS 1
#define COMPACT_JK_ENABLED 2
#define COMPACT_JK_FEATURED 3
#define COMPACT_JK_ONE 4
#define COMPACT_JK_TWO 5
#define COMPACT_JK_THREE 6
#define COMPACT_JK_CONTENTS 7
#define COMPACT_JK_OPTIONS 8
#define COMPACT_JV_DEGREES_CELSIUS 100
#define COMPACT_JV_RELATIVE_HUMIDITY 101




// _my_trie: CharMap
TRIE_CHAR_CODE _my_trie_cm(TRIE_CHAR_CODE c) {
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
    if (c == 'p') return 18;
    if (c == 'v') return 19;
    if (c == 'h') return 20;
    if (c == 'm') return 21;
    if (c == 'y') return 22;
    if (c == 'w') return 23;
    return 0;
}

TRIE_CHAR_CODE _my_trie_chars[] = { '*', 'c', 'o', 'n', 't', 'e', 's', 'd', 'g', 'r', '_', 'l', 'i', 'u', 'a', 'b', 'f', 'p', 'v', 'h', 'm', 'y', 'w' };

// _my_trie: GetToken
TRIE_TOKEN _my_trie_token(uint32_t index, noizu_trie_definition* definition, uint8_t* has_token) {
    *has_token = 1;
    TRIE_TOKEN token = 0;

    if (index == 8) token = COMPACT_JK_CONTENTS;
    else if (index == 23) token = COMPACT_JV_DEGREES_CELSIUS;
    else if (index == 30) token = COMPACT_JK_ENABLED;
    else if (index == 38) token = COMPACT_JK_FEATURED;
    else if (index == 43) token = COMPACT_JK_FIELDS;
    else if (index == 46) token = COMPACT_JK_ONE;
    else if (index == 52) token = COMPACT_JK_OPTIONS;
    else if (index == 69) token = COMPACT_JV_RELATIVE_HUMIDITY;
    else if (index == 74) token = COMPACT_JK_THREE;
    else if (index == 76) token = COMPACT_JK_TWO;
    else *has_token = 0;

    return token;
}



// _my_trie: Node Binary| Bits per field = 11, required = 106
unsigned char _my_trie_node_map[] = {
0X08,0X22,0X44,0X60,
0X90,0X12,0X82,0X60,
0X48,0X09,0X41,0X38,
0X08,0X7C,0XC0,0XA4,
0X15,0X02,0X60,0X4C,
0X09,0XC1,0X58,0X22,
0X04,0XC0,0XB0,0X13,
0X82,0XD0,0X5C,0X09,
0XC0,0X31,0XE4,0X05,
0XE0,0XC0,0X16,0X02,
0X60,0X50,0X04,0X5B,
0X31,0XEF,0X04,0XA0,
0XB8,0X15,0X02,0X60,
0X50,0X03,0X41,0X30,
0X2C,0X05,0000,0X9C,
0X01,0XA6,0X41,0X4C,
0X04,0X81,0X28,0X2D,
0X04,0X60,0X90,0X13,
0X80,0XA8,0XCC,0X0B,
0X01,0X78,0X25,0X05,
0XA0,0XCC,0X13,0X02,
0XB0,0X68,0X0B,0X81,
0XA8,0X2D,0X05,0000,
0XB4,0X12,0X83,0X60,
0X0A,0X0D,0X09,0X50,
0X26,0X04,0XC0,0X5C,
0X11,0X80, };


// _my_trie: Compact Trie Definition, max_sibling_jump=17 rows
struct noizu_trie__compact__definition _my_trie_inner_def = {
    .size = 77,
    .tokens = 10,
    .characters = 23,
    .bit_length__character_code = 5,
    .bit_length__sibling_relative_index = 5,
    .bit_length__child_relative_index = 1,
    .bit_length__child_relative_offset = 10,
    .bit_length = 11,
    .trie_raw = _my_trie_node_map,
    .trie_raw_length = 106,
    .char_map = _my_trie_chars,
    .token_code = _my_trie_token,
    .char_code = _my_trie_cm
};

struct noizu_trie_definition _my_trie = {
    .constant = 1,
    .type = TRIE_COMPACT_TYPE,
    .type_definition = &_my_trie_inner_def,
    .trie_init = noizu_trie__compact__init,
    .trie_free = noizu_trie__compact__free,
    .trie_validate = noizu_trie__compact__validate,
    .trie_advance = noizu_trie__compact__advance,
    .trie_tokenize = NULL
};








TEST_SETUP(TrieCompact)
{
}

TEST_TEAR_DOWN(TrieCompact)
{
}



TEST(TrieCompact, UnitTest_ParseToDelim_KL1_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 1,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));    
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
        }
    }    
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);



    TEST_ASSERT_EQUAL(state.terminator, '+');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}

TEST(TrieCompact, UnitTest_ParseToDelim_KL0_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '+');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}

TEST(TrieCompact, UnitTest_ParseToDelim_KL0_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '+');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}



TEST(TrieCompact, UnitTest_ParseToDelim_KL1_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 1,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '+');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}







TEST(TrieCompact, UnitTest_ParseToEnd_KL1_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 1,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '\0');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}

TEST(TrieCompact, UnitTest_ParseToEnd_KL0_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '\0');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}

TEST(TrieCompact, UnitTest_ParseToEnd_KL0_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '\0');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}



TEST(TrieCompact, UnitTest_ParseToEnd_KL1_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 1,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_INPUT_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_MATCH);


    TEST_ASSERT_EQUAL(state.terminator, '\0');
    TEST_ASSERT_EQUAL(state.skip_next, 0);
}






TEST(TrieCompact, UnitTest_Partial_KL1_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 1,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius_degreg+++");
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_PARSE_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.last_token, 0);    
    TEST_ASSERT_EQUAL(state.match_type, TRIE_PARTIAL_MATCH);

    TEST_ASSERT_EQUAL(state.skip_next, 0);
}


TEST(TrieCompact, UnitTest_Partial_KL0_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius_degreg+++");
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_END_PARSE_EXIT);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.last_token, 0);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_LAST_MATCH);

    TEST_ASSERT_EQUAL(state.skip_next, 0);
}





TEST(TrieCompact, UnitTest_BuffEnd_KL0_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
            req->buffer_pos = 12;
            req->buffer_size = 27;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };


    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_BUFFER_END);
    TEST_ASSERT_EQUAL(state.token, COMPACT_JV_DEGREES_CELSIUS);
    TEST_ASSERT_EQUAL(state.token_index, 23);
    TEST_ASSERT_EQUAL(state.last_token, 0);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_LAST_MATCH);
    TEST_ASSERT_EQUAL(state.skip_next, 1);
}


TEST(TrieCompact, UnitTest_BuffEnd_KL0_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
            req->buffer_pos = 12;
            req->buffer_size = 27;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };

    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_BUFFER_END);
    TEST_ASSERT_EQUAL(state.token, 0);
    TEST_ASSERT_EQUAL(state.token_index, 0);
    TEST_ASSERT_EQUAL(state.last_token, 0);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_NO_MATCH);
    TEST_ASSERT_EQUAL(state.skip_next, 1);
}


TEST(TrieCompact, UnitTest_BuffEarlyEnd_KL0_EB1)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 1,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
            req->buffer_pos = 12;
            req->buffer_size = 20;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };

    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_BUFFER_END);
    TEST_ASSERT_EQUAL(state.token, 0);
    TEST_ASSERT_EQUAL(state.token_index, 0);
    TEST_ASSERT_EQUAL(state.last_token, 0);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_NO_MATCH);
    TEST_ASSERT_EQUAL(state.skip_next, 1);
}


TEST(TrieCompact, UnitTest_BuffEarlyEnd_KL0_EB0)
{
    struct noizu_trie_options options = {
        .deliminator = '+',
        .keep_last_token = 0,
        .end_of_buffer_token = 0,
    };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    if (req) {
        req->buffer = calloc(256, sizeof(uint8_t));
        if (req->buffer) {
            sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
            req->buffer_pos = 12;
            req->buffer_size = 20;
        }
    }
    TEST_ASSERT_NOT_NULL(req);
    TEST_ASSERT_NOT_NULL(req ? req->buffer : NULL);
    struct noizu_trie_state state = { 0 };

    TRIE_TOKEN o = noizu_trie__init(req, &_my_trie, options, &state);
    TEST_ASSERT_TRUE(o, TRIE_INITIALIZED);
    o = noizu_trie__tokenize(&state, &_my_trie, NULL);
    TEST_ASSERT_EQUAL(o, TRIE_BUFFER_END);
    TEST_ASSERT_EQUAL(state.token, 0);
    TEST_ASSERT_EQUAL(state.token_index, 0);
    TEST_ASSERT_EQUAL(state.last_token, 0);
    TEST_ASSERT_EQUAL(state.match_type, TRIE_NO_MATCH);
    TEST_ASSERT_EQUAL(state.skip_next, 1);
}