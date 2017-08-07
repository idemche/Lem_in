/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_holes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 22:02:48 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:47:48 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	lemin_validate_hole(t_lemin *lemin, char *line)
{
	char	**split;
	int		iter;
	int		spaces;

	if (!line || *line == 'L')
		return (0);
	iter = -1;
	spaces = 0;
	if (!(split = ft_strsplit(line, 32)))
		return (0);
	if (!split[1] || !split[2] || split[3])
		return (lemin_free_split(split));
	while (line[++iter])
		if (line[iter] == 32)
			spaces++;
	if (spaces != 2)
		return (lemin_free_split(split));
	lemin_free_split(split);
	return (!lemin_get_hole(lemin, line, 'h'));
}

static void		lemin_add_new_hole(t_lemin *lemin, char *name, char gate)
{
	t_hole	*hole;

	hole = lemin->holes;
	if (!hole)
	{
		if (!(lemin->holes = NEW(t_hole)))
			exit(0 * (int)write(2, "Lemin_add_hole malloc error\n", 28));
		*lemin->holes = (t_hole){0, -1, gate, ft_strdup(name), NULL, NULL};
	}
	else
	{
		while (hole->next)
			hole = hole->next;
		if (!(hole->next = NEW(t_hole)))
			exit(0 * (int)write(2, "Lemin_add_hole malloc error\n", 28));
		*hole->next = (t_hole){0, -1, gate, ft_strdup(name), NULL, NULL};
	}
}

static t_bool	lemin_start_end(t_lemin *lemin, char *line, char *gate)
{
	if ((ft_strequ("##start", line) && !lemin_get_hole(lemin, "s", 'g'))
			|| (ft_strequ("##end", line) && !lemin_get_hole(lemin, "e", 'g')))
	{
		*gate = line[2];
		free(line);
		return (1);
	}
	return (0);
}

t_bool			lemin_parse_holes(t_lemin *lemin)
{
	char	gate;
	char	*line;
	char	**split;

	gate = 0;
	while ((get_next_line(lemin->fd, &line) > 0) && lemin_map(lemin, line))
	{
		(*line == '#') ? lemin_pass_commentaries(lemin, &line) : 0;
		if (lemin_start_end(lemin, line, &gate))
			continue;
		if (!lemin_validate_hole(lemin, line))
			break ;
		else
		{
			lemin_add_new_hole(lemin, (split = ft_strsplit(line, 32))[0], gate);
			lemin_free_split(split);
			free(line);
		}
		gate = 0;
	}
	return (!lemin->holes || lemin_parse_links(lemin, line) == -1 ?
			(t_bool)0 : (t_bool)1);
}
