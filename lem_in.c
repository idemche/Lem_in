/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 18:13:10 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:57:11 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	lemin_free_storage(t_storage *storage)
{
	t_storage *next;

	while (storage)
	{
		next = storage->next;
		free(storage);
		storage = next;
	}
	return (1);
}

void	lemin_release_storage(t_lemin *lemin)
{
	t_storage *storage;
	t_storage *completed;

	storage = lemin->storage;
	while (storage)
	{
		completed = storage->next;
		if (storage->line)
		{
			write(1, storage->line, ft_strlen(storage->line));
			write(1, "\n", 1);
		}
		free(storage->line);
		free(storage);
		storage = completed;
	}
}

void	lemin_free_base(t_lemin *lemin)
{
	t_hole *hole;
	t_link *link;
	t_link *iter;

	while (HOLES)
	{
		hole = HOLES->next;
		link = HOLES->links;
		while (link)
		{
			iter = link->next;
			free(link);
			link = iter;
		}
		free(HOLES->name);
		free(HOLES);
		HOLES = hole;
	}
}

int		main(int argc, char **argv)
{
	t_lemin lemin;

	(void)argv;
	if (argc > 1)
		return ((int)write(2, "Usage: ./lem-in < [map]\n", 24));
	lemin = (t_lemin){0, 0, NULL, NULL, NULL, NEW(t_storage)};
	*lemin.storage = (t_storage){NULL, NULL};
	if (lemin_parse_ants(&lemin) < 1)
		return (lemin_free_storage(lemin.storage) &&
				(int)write(2, "Error parsing ants\n", 19));
	else if (!lemin_parse_holes(&lemin))
		return ((int)write(2, "Error parsing holes/links\n", 26));
	lemin_ordering(&lemin);
	lemin_release_storage(&lemin);
	lemin_advance(&lemin);
	lemin_free_base(&lemin);
	return (0);
}
