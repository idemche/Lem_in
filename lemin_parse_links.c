/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 22:02:48 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 19:08:38 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lemin_create_link(t_hole *one, t_hole *two)
{
	t_link	*link;
	t_link	*find;

	if (one == two)
		return ;
	find = one->links;
	while (find && !(one->gate && two->gate))
	{
		if (find->hole == two)
			return ;
		find = find->next;
	}
	if (!(link = NEW(t_link)))
		exit((int)write(2, "lemin_create_link malloc error!\n", 32) * 0);
	*link = (t_link){two, one->links};
	one->links = link;
}

t_bool		lemin_validate_link(t_lemin *lemin, char *line)
{
	char		**split;
	unsigned	dashes;
	int			iter;

	dashes = 0;
	iter = -1;
	if (line && line[1] == '-')
	{
		split = ft_strsplit(line, '-');
		if (!split[1] || split[2])
			return (lemin_free_split(split));
		if (!lemin_get_hole(lemin, split[0], 'h')
			|| !lemin_get_hole(lemin, split[1], 'h'))
			return (lemin_free_split(split));
		lemin_free_split(split);
		while (line[++iter])
			if (line[iter] == '-')
				dashes++;
		if (dashes != 1)
			return (0);
	}
	return (line && *line ? 1 : 0);
}

char		lemin_parse_links(t_lemin *lemin, char *line)
{
	t_hole	*holes[2];
	char	gnl;
	char	**split;

	gnl = 1;
	while (gnl > 0)
	{
		if (*line == '#')
			lemin_pass_commentaries(lemin, &line);
		if (!lemin_validate_link(lemin, line))
		{
			free(line);
			return (0);
		}
		split = ft_strsplit(line, '-');
		lemin_create_link(holes[0] = lemin_get_hole(lemin, split[0], 'h'),
			holes[1] = lemin_get_hole(lemin, split[1], 'h'));
		lemin_free_split(split);
		lemin_create_link(holes[1], holes[0]);
		free(line);
		gnl = (char)get_next_line(lemin->fd, &line);
		lemin_map(lemin, line);
	}
	free(line);
	return (gnl);
}
