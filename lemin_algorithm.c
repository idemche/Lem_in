/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 19:40:24 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 17:58:01 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	lemin_choose_way(t_lemin *lemin, t_hole *current, int free_ants)
{
	t_bool gone;
	t_hole *next;

	gone = 0;
	if (current == START)
		next = lemin_get_a_path(lemin, current, free_ants);
	else
	{
		next = current->links->hole;
		next = next == START ?
		current->links->next->hole : current->links->hole;
	}
	if (next)
		(gone = 1) &&
		lemin_make_a_move(current, next);
	return (gone);
}

void	lemin_ant_turn(t_lemin *lemin, int ant_index)
{
	int		ant;
	t_link	*head;
	t_hole	*hole;

	ant = ant_index;
	head = START->links;
	while (ant <= lemin->all_ants)
	{
		if ((hole = lemin_get_ant_index(lemin, ant)))
		{
			if (!lemin_choose_way(lemin, hole, lemin->all_ants - ant + 1)
				&& hole == START)
				break ;
			else if (!lemin_get_ant_index(lemin, ant) && hole == START)
				START->links = START->links->next;
		}
		ant++;
	}
	START->links = head;
}

void	lemin_advance(t_lemin *lemin)
{
	int	ant_index;

	ant_index = 1;
	while (START->ants < lemin->all_ants
		|| lemin_get_ant_index(lemin, ant_index))
	{
		lemin_ant_turn(lemin, ant_index);
		while (!lemin_get_ant_index(lemin, ant_index)
			&& ant_index < lemin->all_ants)
			ant_index++;
		write(1, "\n", 1);
	}
}
