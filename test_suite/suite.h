#pragma once

#include "unity.h"


#define TEST_ASSERT_TOKENIZER_STATE(outcome, state, expected_outcome, expected_match_type, expected_token, expected_last_token, expected_skip, expected_terminator) TEST_ASSERT_EQUAL_MESSAGE((expected_outcome), (outcome), "TOKENIZER RESPONSE CODE FAIL");  TEST_ASSERT_EQUAL_MESSAGE((expected_match_type), (state)->match_type, "TOKENIZER MATCH_TYPES FAIL"); TEST_ASSERT_EQUAL_MESSAGE((expected_token), (state)->token, "TOKENIZER TOKEN FAIL");  TEST_ASSERT_EQUAL_MESSAGE((expected_last_token), (state)->last_token, "TOKENIZER LAST TOKEN FAIL"); TEST_ASSERT_EQUAL_MESSAGE((expected_skip), (state)->skip_next, "TOKENIZER SKIP CHAR FAIL"); TEST_ASSERT_EQUAL_MESSAGE((expected_terminator), (state)->terminator, "TOKENIZER END TERMINATOR FAIL")

