#pragma once
#include "noizu_trie.h"
#include "trie_struct/noizu_trie_s.h"
#include "suite.h"

#define STRUCT_HELLO 120
#define STRUCT_HELLO_HELLO 130
#define STRUCT_JK_FIELDS 1
#define STRUCT_JK_ENABLED 2
#define STRUCT_JK_FEATURED 3
#define STRUCT_JK_ONE 4
#define STRUCT_JK_TWO 5
#define STRUCT_JK_THREE 6
#define STRUCT_JK_CONTENTS 7
#define STRUCT_JK_OPTIONS 8
#define STRUCT_JV_DEGREES_CELSIUS 100
#define STRUCT_JV_RELATIVE_HUMIDITY 101
#define STRUCT_JV_DEGREES_CELSIUS_CONTENTS 102

#define STRUCT_SENTINEL_HALT_ON_CONTENTS 123

extern struct noizu_trie_definition struct_test_trie;
