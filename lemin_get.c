/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 17:59:05 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:00:17 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_hole	*lemin_get_ant_index(t_lemin *lemin, int ant)
{
	t_hole *hole;

	hole = HOLES;
	while (hole && hole->ants != ant)
		hole = hole->next;
	return (hole);
}

size_t	lemin_get_link_index(t_hole *hole)
{
	size_t index;
	t_link *link;

	index = 0;
	link = hole->links;
	while (link && ++index)
		link = link->next;
	return (index);
}

t_hole	*lemin_get_hole(t_lemin *lemin, char *name, char type)
{
	t_hole *hole;

	if (!name)
		return (NULL);
	hole = lemin->holes;
	if (type == 'g')
	{
		while (hole && *name != hole->gate)
			hole = hole->next;
	}
	else if (type == 'h')
	{
		while (hole && !ft_strequ(hole->name, name))
			hole = hole->next;
	}
	return (hole);
}

t_hole	*lemin_get_a_path(t_lemin *lemin, t_hole *current, int free_ants)
{
	t_link	*link;
	int		turns;

	link = current->links;
	turns = free_ants + START->depth - 1;
	while (link)
	{
		if (link->hole->ants)
			turns--;
		else if (!link->hole->ants && link->hole->depth <= turns
			&& link->hole->depth != -1)
			return (link->hole);
		link = link->next;
	}
	return ((void*)0);
}
