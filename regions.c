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
    Boolean result = false;

    if( (region_name != NULL) && ((char)*region_name != '\0') && (region_size > 0) && (*regionSearch(region_name) == NULL))
    {
        r_size_t size = roundToEight(region_size, MOD8); //next step before testing; implement in internal_regions.h
        region* new = malloc(sizeof(region)); //allocate memory for new region
        
        if( new != NULL )
        {
            new->blocks = NULL;
            new->memory = malloc(size);
            new->size = size; 
            new->name = (char*)region_name;
            new->next = top;
            top = new;

            selected = new; //assign the new region as the selected region
            
            numRegions++;
            result = true;
        }
    }
    //should create method to ensure region is valid...
    return result;
}

Boolean rchoose( const char *region_name )
{
    Boolean result = false;

    if( (region_name != NULL) && ((char)*region_name != '\0') )
    {
        region* toSelect = *regionSearch(region_name);
        if( toSelect != NULL)
        {
            selected = toSelect;
            result = true;
        }
    }

    // workin on that region validator meow... >.<

    return result;
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

//functions below are designed to help find regions and blocks

region** regionSearch (const char* name)
{
    region** curr = &top //pointer to the address of top in order to locate the proper region

    while(((*curr) != NULL) && (strcmp((*curr)->name, name) != 0))
    {
        curr = &((*curr)-> next);
    }
    return curr;
}

block** blockSearch (region* query, void* address)
{
    block** curr = NULL;
    if(query != NULL && address != NULL)
    {
        curr = &(query->blocks);
        while((*curr != NULL) && ((*curr)->start != address))
        {
            curr = &((*curr)->next);
        }
    }
    return curr;
}

//functions below are for aquiring and manipulating blocks of memory

Boolean freeBlock (block** delete)
{
    Boolean result = false; 
    if ((delete != NULL) && (*delete != NULL))
    {
        block* old = *delete; 
        *delete = (*delete)->next;
        free(old);
        result = true;
    }
    return result;
} 