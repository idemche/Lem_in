/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 13:57:57 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:17:34 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/includes/libft.h"

# define INT_MAX	2147483647
# define START		lemin->start
# define END		lemin->end
# define HOLES		lemin->holes
# define NEW(x)		(x*)malloc(sizeof(x))
# define SPACED(x)	(x == ' ' || x == '\r')
# define TABBED(x)	(x == '\t' || x == '\v' || x == '\f' || x == '\n')
# define DIGIT(x)	(x >= 48 && x <= 57)

typedef unsigned char	t_bool;
typedef struct			s_hole
{
	int				ants;
	int				depth;
	char			gate;
	char			*name;
	struct s_link	*links;
	struct s_hole	*next;
}						t_hole;

typedef struct			s_link
{
	t_hole			*hole;
	struct s_link	*next;
}						t_link;

typedef struct			s_storage
{
	char				*line;
	struct s_storage	*next;
}						t_storage;

typedef struct			s_lemin
{
	int				fd;
	int				all_ants;
	t_hole			*start;
	t_hole			*holes;
	t_hole			*end;
	t_storage		*storage;
}						t_lemin;

/*
**  LEMIN PARSE ANTS
*/

int						lemin_atoi(char *str);
int						lemin_parse_ants(t_lemin *lemin);
t_bool					lemin_map(t_lemin *lemin, char *line);
t_bool					lemin_pass_commentaries(t_lemin *lemin, char **line);

/*
**  LEMIN PARSE HOLES
*/

t_bool					lemin_parse_holes(t_lemin *lemin);

/*
** LEMIN PARSE LINKS
*/

char					lemin_parse_links(t_lemin *lemin, char *line);

/*
**  WEAK FUNCTIONS
*/

t_bool					lemin_free_split(char **split);

/*
**  LEMIN ORDERING DATA
*/

void					lemin_ordering(t_lemin *lemin);
void					lemin_order_stack(t_lemin *lemin);
void					lemin_prune_branch(t_lemin *lemin);
void					lemin_delete_deprecated(t_lemin *lemin);
void					lemin_recreate_depth(t_hole *hole, int depth);
void					lemin_sort_links_by_depth(t_lemin *lemin);

/*
** LEMIN GETTERS/SETTERS
*/

size_t					lemin_get_link_index(t_hole *hole);
t_hole					*lemin_get_ant_index(t_lemin *lemin, int ant);
t_hole					*lemin_get_hole(t_lemin *lemin, char *name, char type);
t_hole					*lemin_get_a_path(t_lemin *lemin,
	t_hole *current, int free_ants);

/*
** LEMIN ALGO
*/

void					lemin_advance(t_lemin *lemin);
t_bool					lemin_make_a_move(t_hole *from, t_hole *to);

#endif
