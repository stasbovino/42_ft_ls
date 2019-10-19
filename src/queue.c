#include "ft_ls.h"

int			add_to_queue(t_queue **start, char *curr)
{
	t_queue *tmp;
	t_queue *new;

	tmp = *start;
	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (1);
	new->next = NULL;
	new->name = curr;
	if (!tmp)
	{
		*start = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
