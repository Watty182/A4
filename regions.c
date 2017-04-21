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

int numRegs = 0;
int numBlks = 0;

region* top = NULL;
region* selected = NULL;

Boolean rinit( const char *region_name, r_size_t region_size )
{
#ifndef NDEBUG
    assert(region_name != NULL);
    assert((char)*region_name != '\0');
    assert(region_size > 0);
#endif

    Boolean result = false;

    if( (region_name != NULL) && ((char)*region_name != '\0') && (region_size > 0) && (*regionSearch(region_name) == NULL))
    {
        r_size_t size = roundToEight(region_size, MOD8); //next step before testing; implement in internal_regions.h
        region* new = malloc(sizeof(region)); //allocate memory for new region

#ifndef NDEBUG
    assert(new != NULL);
#endif

        if( new != NULL )
        {
            new->blocks = NULL;
            new->memory = malloc(size);
            new->size = size; 
            new->name = (char*)region_name;
            new->next = top;
            top = new;

            selected = new; //assign the new region as the selected region
            
            numRegs++;
            result = true;
        }
    }
    //should create method to ensure region is valid...and done(?)
    validationStation();
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
    validationStation();
    return result;
}

const char *rchosen()
{
    char* result = NULL;
    if( selected != NULL )
    {
        result = selected->name;
    }
    validationStation();

    return result;
}

void *ralloc( r_size_t block_size )
{
    //starting assertions from the get-go b/c ez-er
#ifndef NDEBUG
    assert(selected != NULL);
    assert(block_size > 0);
    assert(block_size <= selected->size);
#endif

    void* result = NULL;

    if( (selected != NULL) && (block_size > 0) && (block_size <= selected->size) )
    {
        //acquire a block... 
        block* new = validBlock(selected, roundToEight(block_size, MOD8));
        if( new != NULL )
        {
            result = new->start;
            numBlks++;
        }
    }
}

r_size_t rsize( void *block_ptr )
{
#ifndef NDEBUG
    assert(block_ptr != NULL);
#endif

    int size = 0;
    block** pickBlk = blockSearch(selected, block_ptr);

    if( (pickBlk != NULL) && ((*pickBlk) != NULL) )
    {
        size = (*select)->size;
    } 

    validationStation();

    return size;
}

Boolean rfree( void *block_ptr )
{
    Boolean result = false;
    
#ifndef NDEBUG
    assert(selected != NULL);
    assert(block_ptr != NULL);
#endif

    if(freeBlock(blockSearch(selected, block_ptr)))
    {
        result = true;
        numBlks--;
    }
    validationStation();

    return result;
}

void rdestroy( const char *region_name )
{
#ifndef NDEBUG
    assert(region_name != NULL);
    assert((char)*region_name != '\0');
#endif

    if( (region_name != NULL) && ((char)*region_name != '\0')) 
    {
        region** toDestroy = regionSearch(region_name);
        if( (toDestroy != NULL) && (*toDestroy != NULL) )
        {
            if( selected == *toDestroy )
            {
                selected == NULL;
            }
            while( (*toDestroy)->blocks != NULL)
            {
                freeBlock(blockSearch(*toDestroy, (*toDestroy)->blocks->start));
                numBlks--;
            }
            free((*toDestroy)->memory);
            region* toFree = *toDestroy;
            *toDestroy = (*toDestroy)->next;
            free(toFree);
            numRegs--;
        }
    }
    validationStation();
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

//functions below are for acquiring and manipulating blocks of memory

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

//traverse list of regions and ensure number of regions and blocks
//counted are equal to current number of regions and blocks created
void validationStation()
{
    //... count regions and blocks to start

    int acqReg = 0;
    int acqBlk = 0;


    region* curReg = top;
    
    while( curReg != NULL ) //region traversal
    {
#ifndef NDEBUG
    assert(curReg->name != NULL);
    assert(curReg->name[0] != '\0');
    assert(curReg->size > 0);
    assert((curReg->size % 8) == 0)
    assert(curReg->memory != NULL);
#endif

        void* memLocation = NULL;
        int memoryUsed = 0;
        
        block* curBlk = curReg->blocks;

        while( curBlk != NULL ) //block traversal
        {

#ifndef NDEBUG
    assert(curBlk->start != NULL);
    assert((curBlk->start - curReg->memory) < curReg->size);
    assert(curBlk->size > 0);
    assert((curBlk->size % 8) == 0);
    assert(curBlk->start > memLocation);
#endif

            memLocation = curBlk->start;
            memoryUsed += curBlk->size;

#ifndef NDEBUG
    assert(memoryUsed <= curReg->size);
#endif

            acqBlk++;

            curBlk = curBlk->next;
        }
        acqReg++;
        curReg = curReg->next;
    }

    //... need assertions... everywhere.
}
//ensures value passed to function is going to return as the next possible value of 8
r_size_t roundToEight(r_size_t val, int mtpl)
{
    return (r_size_t)((((int)((val-1)/mtpl))+1) * mtpl);
}

//get the blocks of a region, traverse the blocks until there is space, allocate more memory,
// and return a pointer to the block.
block* validBlock(region* reg, r_size_t size)
{
    block* new = NULL;
    if(reg != NULL)
    {
        int end = 0; //placehold the end of the blocks
        void* start = reg->memory; //placehold the start of the blocks of memory

        block* curr =  reg->blocks;
        block** next = &(reg->blocks); //for use of ease of traversal

        Boolean room = false;

        if( ((curr == NULL) && (reg->size >= size)) || ((curr != NULL) && ((curr->start - start) >= size)) )
        {
            room = true;
        }

        while( (curr != NULL) && !room)
        {
            start = curr->start + curr->size;
            end = start - reg->memory;
            next = &(curr->next);

            if( curr->next != NULL && ((curr->next->start - start) >= size) ) //if next block is not null, and holds more than size required
            {
                room = true;
            }
            if( curr->next == NULL && ((reg->size - end) >= size)) //if remaining size in region is larger than required size
            {
                room = true;
            }
            if( !room ) //move to next block
            {
                curr = curr->next;
            }
        }
        if (room)
        {
            new = reBlock(start, size, *next);
            
            *next = new;
        }
    }
}

// Fill a block of memory with 0s to help reallocate memory.
block* reBlock(void* start, r_size_t size, block* next)
{
    block* new = malloc(sizeof(block));

    if( new != NULL )
    {
        new->start = start;
        new->size = size;
        new->next = next;
        memset(new->start, 0, new->size); // 
    }

    return new;
}