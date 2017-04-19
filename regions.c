//-------------------------------------------------------------------------------
// NAME: Ryan Watkins
// STUDENT NUMBER: 7691844
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 4
//
// REMARKS: This program will implement named memory regions, 
// where each region is given a name (a string) and referred to by that name. 
// Each region has a fixed maximum size that is specified when it is created. 
// Within each region, blocks of memory can be allocated and freed, 
// totalling up to its maximum size.
//-------------------------------------------------------------------------------

#include "regions.h"
#include "internal_regions.h"

// define architecture of memory regions

typedef struct REGION 
{
    region *next;
    void* memory;
    char* name;
    int size;
    block* blocks;
} region;

typedef struct BLOCK 
{
    block* next;
    void *start;
    int size;
} block;

int numRegions = 0;
int numBlocks = 0;

region* top = NULL;
region* selected = NULL;

Boolean rinit( const char *region_name, r_size_t region_size )
{

}

Boolean rchoose( const char *region_name )
{

}

const char *rchosen()
{

}

void *ralloc( r_size_t block_size )
{

}

r_size_t rsize( void *block_ptr )
{

}

Boolean rfree( void *block_ptr )
{

}

void rdestroy( const char *region_name )
{

}

void rdump()
{

}