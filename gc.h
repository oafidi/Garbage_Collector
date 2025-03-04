#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_allocation
{
    void                *ptr;
    struct s_allocation *next;
}   t_allocation;

void    *gc_malloc(size_t size, int function);

#endif