#include <stdio.h>
#include <string.h>
#include "person.h"


int main(int argc, char* argv[]){


    if ( strcmp(argv[1],"-i") == 0 )
    {
        add(argv[2], argv[3]);
    }

    if ( strcmp(argv[1],"-l") == 0 )
    {
        list(argv[2]);
    }

    if ( strcmp(argv[1],"-u") == 0 )
    {
        update(argv[2], argv[3]);
    }

    if ( strcmp(argv[1],"-o") == 0 )
    {
        update_o(argv[2], argv[3]);
    }

    return 0;
}
