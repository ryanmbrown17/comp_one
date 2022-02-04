#ifndef TREE_H
#define TREE_H

#include "my_string.h"
#include "generic_vector.h"
typedef void* TREE;
TREE tree_init_default(void);
Status tree_add_words(GENERIC_VECTOR hVector, TREE* phTree, MY_STRING old_key, char guess);
MY_STRING tree_key_find(TREE hTree, GENERIC_VECTOR hVector);
void tree_destroy(TREE* phTree);
#endif 
