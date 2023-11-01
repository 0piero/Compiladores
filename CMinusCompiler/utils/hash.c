#include "hash.h"
int hash_func(int n){ return ((5 * n + 4) % 8999) % 7; }