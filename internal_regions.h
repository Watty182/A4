#ifndef _INTERNAL_REGIONS_H
#define _INTERNAL_REGIONS_H

#define MOD8 8

r_size_t roundToEight( r_size_t, int );
region** regionSearch( const char* );
block** blockSearch( region*, void* );
Boolean freeBlock( block** );
#endif