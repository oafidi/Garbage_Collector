#include "gc.h"

static t_allocation	*new_node(void *content)
{
	t_allocation *rtn;

	rtn = (t_allocation *)malloc(sizeof(t_allocation));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->ptr = content;
	return (rtn);
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

void    *gc_malloc(size_t size, int function)
{
    static t_allocation *head;
    t_allocation        *new;
    void                *ptr;

    if (function == 1)
    {
        ptr = malloc(size);
        if (!ptr)
            return (lst_clear(&head), NULL);
        new = new_node(ptr);
        if (!new)
            return (lst_clear(&head), free(ptr), NULL);
        lst_addfront(&head, new);
        return (ptr);
    }
    else if (function == 0)
    {
        lst_clear(&head);
        return (NULL);
    }
}

int main()
{
    char *str = gc_malloc(2, 1);

    str[0] = 'a';
    str[1] = 0;

    printf("%p\n", str);
    gc_malloc(0, 0);
    printf("%p\n", str);
}