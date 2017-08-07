/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 20:59:20 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:03:02 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		lemin_map(t_lemin *lemin, char *line)
{
	t_storage *storage;

	if (!line)
		return (0);
	storage = lemin->storage;
	while (storage->next)
		storage = storage->next;
	storage->next = (t_storage*)malloc(sizeof(t_storage));
	*storage->next = (t_storage){ft_strdup(line), NULL};
	return (1);
}

t_bool		lemin_pass_commentaries(t_lemin *lemin, char **line)
{
	while (*line
		&& **line == '#'
		&& ft_strcmp(*line, "##start")
		&& ft_strcmp(*line, "##end"))
	{
		lemin_map(lemin, *line);
		free(*line);
		get_next_line(lemin->fd, line);
	}
	return (1);
}

int			lemin_parse_ants(t_lemin *lemin)
{
	int		is_empty;
	char	*line;

	if ((is_empty = get_next_line(lemin->fd, &line)) == -1)
		exit((int)write(2, "FILE DOES NOT EXIST\n", 20));
	else if (!is_empty)
		exit((int)write(2, "FILE IS EMPTY\n", 14));
	lemin_pass_commentaries(lemin, &line);
	lemin_map(lemin, line);
	if (!ft_string_isdigit(line))
		return (-1);
	lemin->all_ants = lemin_atoi(line);
	free(line);
	return (lemin->all_ants);
}
