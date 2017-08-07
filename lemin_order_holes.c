/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_order_holes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:39:21 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:01:16 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lemin_recreate_depth(t_hole *hole, int depth)
{
	t_link *link;

	if (!hole)
		return ;
	hole->depth = depth;
	if (hole->gate != 's' && (link = hole->links))
		while (link)
		{
			if (link->hole->depth > hole->depth + 1 || link->hole->depth == -1)
				lemin_recreate_depth(link->hole, hole->depth + 1);
			link = link->next;
		}
}

static void		lemin_cutoff_link(t_hole *one, t_hole *two)
{
	t_link *cutoff;
	t_link *tmp;

	if (one->links->hole != two)
	{
		tmp = one->links;
		while (tmp && tmp->next->hole != two)
			tmp = tmp->next;
		cutoff = tmp->next;
		tmp->next = tmp->next->next;
	}
	else
	{
		cutoff = one->links;
		one->links = one->links->next;
	}
	free(cutoff);
}

void			lemin_delete_deprecated(t_lemin *lemin)
{
	t_link *link;
	t_hole *holes;

	holes = HOLES;
	while (holes)
	{
		while (holes->links && holes->links->hole->depth == -1)
		{
			link = holes->links;
			holes->links = holes->links->next;
			lemin_cutoff_link(link->hole, holes);
			free(link);
		}
		holes = holes->next;
	}
}

static void		lemin_deep_cutoff(t_hole *one, t_hole *beyond)
{
	t_hole *two;
	t_link *link;

	if (one->gate != 's' && one->gate != 'e')
	{
		link = one->links->next;
		while (2 < lemin_get_link_index(one))
		{
			if (link->hole != beyond)
			{
				two = link->hole;
				lemin_cutoff_link(one, two);
				lemin_cutoff_link(two, one);
				link = one->links;
			}
			link = link->next;
		}
		if (lemin_get_link_index(one) != 1 && one->links->hole == beyond)
			lemin_deep_cutoff(one->links->next->hole, one);
		else if (lemin_get_link_index(one) != 1 && one->links->hole != beyond)
			lemin_deep_cutoff(one->links->hole, one);
	}
}

void			lemin_prune_branch(t_lemin *lemin)
{
	t_link *link;
	t_hole *holes;

	link = START->links;
	holes = HOLES;
	while (link)
	{
		lemin_deep_cutoff(link->hole, START);
		link = link->next;
	}
	while (holes)
	{
		holes->depth = -1;
		holes = holes->next;
	}
}
