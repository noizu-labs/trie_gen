#include "unity.h"
#include "unity_fixture.h"
#include "support/trie_test_fixture.h"

TRIE_TOKEN struct_test_sentinel(TRIE_TOKEN advance_flag, struct noizu_trie_state* state, struct noizu_trie_definition* definition) {

	struct noizu_trie__struct__definition* a_trie = (struct noizu_trie__struct__definition*)definition->type_definition;
	TRIE_TOKEN t = a_trie->trie[state->position].termination_code;
	if (t == STRUCT_JK_CONTENTS) {
		state->token = t;
		state->token_index = state->position;
		state->match_type = TRIE_MATCH;
		return STRUCT_SENTINEL_HALT_ON_CONTENTS;
	}
	if (t == STRUCT_JV_DEGREES_CELSIUS) {
		state->initialized = FALSE;
		state->position = 1;
	}
	return 0;
}


TEST_GROUP(TrieStruct);


TEST_SETUP(TrieStruct)
{
}

TEST_TEAR_DOWN(TrieStruct)
{
}

TEST(TrieStruct, UnitTest_ParseToDelim_KL1_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '+');
}

TEST(TrieStruct, UnitTest_ParseToDelim_KL0_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .end_of_buffer_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '+');
}

TEST(TrieStruct, UnitTest_ParseToDelim_KL0_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+' };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '+');
}



TEST(TrieStruct, UnitTest_ParseToDelim_KL1_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1, .end_of_buffer_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '+');
}







TEST(TrieStruct, UnitTest_ParseToEnd_KL1_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_INPUT_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '\0');
}

TEST(TrieStruct, UnitTest_ParseToEnd_KL0_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .end_of_buffer_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_INPUT_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '\0');
}

TEST(TrieStruct, UnitTest_ParseToEnd_KL0_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+' };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_INPUT_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '\0');
}



TEST(TrieStruct, UnitTest_ParseToEnd_KL1_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1, .end_of_buffer_token = 1, };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius") + 10;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_INPUT_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, '\0');
}






TEST(TrieStruct, UnitTest_Partial_KL1_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsiusc_degreg+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_PARSE_EXIT, TRIE_PARTIAL_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, 'c');
}


TEST(TrieStruct, UnitTest_Partial_KL0_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+' };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsiusc_degreg+++");
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_PARSE_EXIT, TRIE_LAST_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, 'c');
}





TEST(TrieStruct, UnitTest_BuffEnd_KL0_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .end_of_buffer_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
    req->buffer_pos = 12;
    req->buffer_size = 27;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_BUFFER_END, TRIE_LAST_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 1, '\0');
}


TEST(TrieStruct, UnitTest_BuffEnd_KL0_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+' };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
    req->buffer_pos = 12;
    req->buffer_size = 27;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_BUFFER_END, TRIE_NO_MATCH, 0, 0, 1, '\0');
}


TEST(TrieStruct, UnitTest_BuffEarlyEnd_KL0_EB1)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .end_of_buffer_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
    req->buffer_pos = 12;
    req->buffer_size = 20;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_BUFFER_END, TRIE_NO_MATCH, 0, 0, 1, '\0');
}


TEST(TrieStruct, UnitTest_BuffEarlyEnd_KL0_EB0)
{
    struct noizu_trie_options options = { 0, .delimiter = '+' };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    sprintf_s(req->buffer, 256, "beforefor+++degrees_celsius_degreg+++");
    req->buffer_pos = 12;
    req->buffer_size = 20;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_BUFFER_END, TRIE_NO_MATCH, 0, 0, 1, '\0');
}






TEST(TrieStruct, UnitTest_Sentinel_On)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsiuscontentsrelative_humiditydegrees_celsius");
    req->buffer_pos = 0;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, struct_test_sentinel);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_PARTIAL_SENTINEL_EXIT, TRIE_MATCH, STRUCT_JK_CONTENTS, STRUCT_JV_DEGREES_CELSIUS, 0, '\0');
    TEST_ASSERT_EQUAL(state.sentinel_exit_code, STRUCT_SENTINEL_HALT_ON_CONTENTS);
}



TEST(TrieStruct, UnitTest_Sentinel_Off)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsiuscontentsrelative_humiditydegrees_celsius");
    req->buffer_pos = 0;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_END_PARSE_EXIT, TRIE_PARTIAL_MATCH, STRUCT_JV_DEGREES_CELSIUS, 0, 0, 'c');
    TEST_ASSERT_EQUAL(state.sentinel_exit_code, 0);
}



TEST(TrieStruct, UnitTest_RunOn)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "degrees_celsius_contents+relative_humiditydegrees_celsius");
    req->buffer_pos = 0;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_JV_DEGREES_CELSIUS_CONTENTS, STRUCT_JV_DEGREES_CELSIUS, 0, '+');
}




TEST(TrieStruct, UnitTest_HardDelim_On)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1,.hard_delim = 1 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "hello+hello+world");
    req->buffer_pos = 0;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_HELLO, 0, 0, '+');
}




TEST(TrieStruct, UnitTest_HardDelim_Off)
{
    struct noizu_trie_options options = { 0, .delimiter = '+', .keep_last_token = 1,.hard_delim = 0 };
    offset_buffer* req = calloc(1, sizeof(offset_buffer));
    req->buffer = calloc(256, sizeof(uint8_t));
    req->buffer_size = sprintf_s(req->buffer, 256, "hello+hello+world");
    req->buffer_pos = 0;
    struct noizu_trie_state state = { 0 };
    noizu_trie__init(req, &struct_test_trie, options, &state);
    TRIE_TOKEN o = noizu_trie__tokenize(&state, &struct_test_trie, NULL);
    TEST_ASSERT_TOKENIZER_STATE(o, &state, TRIE_DELIM_EXIT, TRIE_MATCH, STRUCT_HELLO_HELLO, STRUCT_HELLO, 0, '+');
}
