#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"

// this code should run to completion with the output shown
// you must think of additional cases of correct use and misuse for your testing
int testsPassed = 0;
int testsFailed = 0;

int main()
{
    Boolean rc;

    rc = rinit("", 300); //disallowed
    assert(!rc);
    rc = rinit("test2", 298);
    assert(rc);
    rc = rinit("test2", 800); //fail; same name
    assert(!rc);
    rc = rinit("test3", 0); //fail; zero size
    assert(!rc);
    rc = rinit("test4", 1); //pass; size 8
    assert(rc);
    rc = rchoose("");
    assert(!rc); 
    rc = rchoose("test2"); //pass
    assert(rc);
    rc = rchoose("dne"); //does not exist
    assert(!rc);

    printf("Program Completed Successfully");    

}


