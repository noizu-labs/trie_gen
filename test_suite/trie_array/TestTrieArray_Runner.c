#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(TrieArray)
{

	RUN_TEST_CASE(TrieArray, UnitTest_ParseToDelim_KL1_EB0);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToDelim_KL0_EB1);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToDelim_KL0_EB0);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToDelim_KL1_EB1);

	RUN_TEST_CASE(TrieArray, UnitTest_ParseToEnd_KL1_EB0);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToEnd_KL0_EB1);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToEnd_KL0_EB0);
	RUN_TEST_CASE(TrieArray, UnitTest_ParseToEnd_KL1_EB1);

	RUN_TEST_CASE(TrieArray, UnitTest_Partial_KL1_EB0);
	RUN_TEST_CASE(TrieArray, UnitTest_Partial_KL0_EB0);

	RUN_TEST_CASE(TrieArray, UnitTest_BuffEnd_KL0_EB1);
	RUN_TEST_CASE(TrieArray, UnitTest_BuffEnd_KL0_EB0);

	RUN_TEST_CASE(TrieArray, UnitTest_BuffEarlyEnd_KL0_EB1);
	RUN_TEST_CASE(TrieArray, UnitTest_BuffEarlyEnd_KL0_EB0);

	RUN_TEST_CASE(TrieArray, UnitTest_Sentinel_On);
	RUN_TEST_CASE(TrieArray, UnitTest_Sentinel_Off);

	RUN_TEST_CASE(TrieArray, UnitTest_RunOn);

	RUN_TEST_CASE(TrieArray, UnitTest_HardDelim_On);
	RUN_TEST_CASE(TrieArray, UnitTest_HardDelim_Off);

	RUN_TEST_CASE(TrieArray, UnitTest_JsonDelim_KL1);
	RUN_TEST_CASE(TrieArray, UnitTest_JsonDelim_KL0);
}