#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void* (*Copy)(void*);
typedef int (*Compare)(void*, void*);
typedef void (*Print)(void*);
typedef void (*Destroy)(void*);
typedef unsigned int (*HashFn)(void* data, int size);

#endif /* _AVL_H_ */