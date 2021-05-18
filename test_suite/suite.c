#include "unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(TrieArray);
	RUN_TEST_GROUP(TrieStruct);
	RUN_TEST_GROUP(TrieCompact);
}


int suite(int argc, const char* argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}