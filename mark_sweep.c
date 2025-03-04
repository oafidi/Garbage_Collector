#include "mark_sweep.h"

static t_allocation	*new_node(void *content)
{
	t_allocation *rtn;

	rtn = (t_allocation *)malloc(sizeof(t_allocation));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->ptr = content;
    rtn->is_marked = 0;
	return (rtn);
}

MemoryManger    *init_MemoryManager(void)
{
    MemoryManger    *manager = malloc(sizeof(MemoryManger));

    if (!manager)
        return (NULL);
    manager->head = NULL;
    return (manager);
}

static void	lst_addfront(t_allocation **head, t_allocation *new)
{
	if (!head || !new)
		return ;
	new->next = *head;
	*head = new;
}

static void	lst_clear(t_allocation **lst)
{
	t_allocation	*list;
	t_allocation	*next;

	if (lst)
	{
		list = *lst;
		while (list)
		{
			next = list->next;
            free(list->ptr);
			free(list);
			list = next;
		}
		*lst = NULL;
	}
}

void    *gc_malloc(MemoryManger *manager, size_t size)
{
    void *ptr;
    t_allocation *object;

    ptr = malloc(size);
    if (!ptr)
        return (lst_clear(&(manager->head)), NULL);
        
    object =  new_node(ptr);
    if (!object)
        return (lst_clear(&(manager->head)), free(ptr), NULL);
    lst_addfront(&(manager->head), object);
    return (ptr);
}

void    gc_mark(MemoryManger *manager, void *ptr)
{
    t_allocation *temp;

    if (!manager)
        return ;
    temp = manager->head;
    while (temp)
    {
        if (temp->ptr == ptr)
        {
            temp->is_marked = 1;
            return ;
        }
        temp = temp->next;
    }
}

void    gc_sweep(MemoryManger *manager)
{
    t_allocation *temp;
    t_allocation *prec;

    if (!manager || !manager->head)
        return ;
    temp = manager->head;
    while (temp && temp->is_marked == 0)
    {
        manager->head = temp->next;
        free(temp->ptr);free(temp);
        temp = manager->head;
    }
    if (temp)
    {   
        prec = temp;
        temp = temp->next;
    }
    while (temp)
    {
        if (temp->is_marked == 0)
        {   
            prec->next = temp->next;
            free(temp->ptr);free(temp);
            temp = prec->next;
        }
        else
        {
            prec = temp;
            temp = temp->next;
        }
    }
}

void    gc_reset_marks(MemoryManger *manager)
{
    t_allocation *temp;

    if (!manager)
        return ;
    temp = manager->head;
    while (temp)
    {
        temp->is_marked = 0;
        temp = temp->next;
    }
}

void    read_memory(MemoryManger *manager)
{
    t_allocation *temp;

    if (!manager)
        return ;
    temp = manager->head;
    while (temp)
    {
        printf("Mark: %d ---> Adrress: %p\n", temp->is_marked, temp->ptr);
        temp = temp->next;
    }
}

int main()
{
    MemoryManger *manager = init_MemoryManager();

    if (!manager)
        return (1);
    char *ptr1 = gc_malloc(manager, 4);
    char *ptr2 = gc_malloc(manager, 4 * 3);
    printf("First read\n");
    read_memory(manager);
    gc_mark(manager, ptr1);
    printf("Second read\n");
    read_memory(manager);
    gc_sweep(manager);
    printf("Third read\n");
    read_memory(manager);
    gc_reset_marks(manager);
    printf("Fourth read\n");
    read_memory(manager);
    gc_sweep(manager);
    printf("Last read\n");
    read_memory(manager);
    free(manager);
}