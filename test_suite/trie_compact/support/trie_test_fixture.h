#pragma once
#include "noizu_trie.h"
#include "trie_compact/noizu_trie_c.h"
#include "suite.h"

#define COMPACT_HELLO 120
#define COMPACT_HELLO_HELLO 130
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
#define COMPACT_JV_DEGREES_CELSIUS_CONTENTS 102

#define COMPACT_SENTINEL_HALT_ON_CONTENTS 123

extern struct noizu_trie_definition compact_test_trie;
