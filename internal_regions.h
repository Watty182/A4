#ifndef _INTERNAL_REGIONS_H
#define _INTERNAL_REGIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regions.h"

#define MOD8 8
typedef struct REGION region;
typedef struct BLOCK block;
r_size_t roundToEight(r_size_t, int);
region **regionSearch(const char *);
block **blockSearch(region *, void *);
Boolean freeBlock(block **);
block *validBlock(region *, r_size_t);
block *reBlock(void *, r_size_t, block *);
int freeRegSpace(region *);
void printBlocks(region *);
void validationStation();
#endif