#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* mystrsep(char** stringp, const char* delim) {
    char* start = *stringp;
    char* p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL) {
        *stringp = NULL;
    } else {
        *p = '\0';
        *stringp = p + 1;
    }

    return start;
}

