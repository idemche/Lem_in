/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_order_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:39:21 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:02:15 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	lemin_links_sort_completed(t_hole *holes)
{
	t_link *links;

	if (holes->links && holes->links->next)
	{
		links = holes->links;
		while (links->next)
		{
			if (links->next->hole->depth < links->hole->depth)
				return (0);
			links = links->next;
		}
	}
	return (1);
}

static void		lemin_swap_links(t_link *one, t_hole *holes)
{
	t_link *link;
	t_link *two;

	two = one->next;
	if (one == holes->links)
		holes->links = two;
	else
	{
		link = holes->links;
		while (link->next != one)
			link = link->next;
		link->next = two;
	}
	one->next = two->next;
	two->next = one;
}

void			lemin_sort_links_by_depth(t_lemin *lemin)
{
	t_link *link;
	t_hole *holes;

	holes = lemin->holes;
	while (holes)
	{
		while (!lemin_links_sort_completed(holes))
		{
			link = holes->links;
			while (link && link->next)
			{
				if (link->next->hole->depth < link->hole->depth)
					lemin_swap_links(link, holes);
				link = link->next;
			}
		}
		holes = holes->next;
	}
}

inline void		lemin_order_stack(t_lemin *lemin)
{
	lemin_recreate_depth(END, 0);
	lemin_sort_links_by_depth(lemin);
	lemin_delete_deprecated(lemin);
}

void			lemin_ordering(t_lemin *lemin)
{
	START = lemin_get_hole(lemin, "s", 'g');
	END = lemin_get_hole(lemin, "e", 'g');
	if (!START || !END || START == END)
		exit((int)write(2, "ERROR WITH START/END\n", 21));
	START->ants = 1;
	lemin_order_stack(lemin);
	if (START->depth == -1)
		exit((int)write(2, "ERROR CONNECTION START/END\n", 27));
	lemin_prune_branch(lemin);
	lemin_order_stack(lemin);
}
