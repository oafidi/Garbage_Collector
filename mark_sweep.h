#ifndef MARK_SWEEP_H
# define MARK_SWEEP_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_allocation
{
    void                *ptr;
    int                 is_marked;
    struct s_allocation *next;
}   t_allocation;

typedef struct MemoryManger
{
    t_allocation *head;
}   MemoryManger;

void    gc_reset_marks(MemoryManger *manager);
void    gc_sweep(MemoryManger *manager);
void    gc_mark(MemoryManger *manager, void *ptr);
void    *gc_malloc(MemoryManger *manager, size_t size);

#endif