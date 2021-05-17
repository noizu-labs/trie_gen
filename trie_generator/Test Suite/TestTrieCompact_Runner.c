#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(TrieCompact)
{
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToDelim_KL1_EB0);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToDelim_KL0_EB1);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToDelim_KL0_EB0);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToDelim_KL1_EB1);

	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToEnd_KL1_EB0);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToEnd_KL0_EB1);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToEnd_KL0_EB0);
	RUN_TEST_CASE(TrieCompact, UnitTest_ParseToEnd_KL1_EB1);

	RUN_TEST_CASE(TrieCompact, UnitTest_Partial_KL1_EB0);
	RUN_TEST_CASE(TrieCompact, UnitTest_Partial_KL0_EB0);

	RUN_TEST_CASE(TrieCompact, UnitTest_BuffEnd_KL0_EB1);
	RUN_TEST_CASE(TrieCompact, UnitTest_BuffEnd_KL0_EB0);

	RUN_TEST_CASE(TrieCompact, UnitTest_BuffEarlyEnd_KL0_EB1);
	RUN_TEST_CASE(TrieCompact, UnitTest_BuffEarlyEnd_KL0_EB0);

	
}