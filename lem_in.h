/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 13:57:57 by idemchen          #+#    #+#             */
/*   Updated: 2017/05/18 20:52:56 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ARRAY_SIZE(x) (sizeof(x) / sizeof(0[a]))

# include <stdlib.h>
# include <unistd.h>
# include "libft/includes/libft.h"

# define INT_MAX 2147483647
# define PARSER base->baseline

typedef struct		s_room
{
	int				poids;
	int				ants;
	int				number;
	int				here;
	char			*name;
	struct s_room	*next;
	struct s_room	**tube;
}					t_room;

typedef struct		s_basis
{
	int		ants;
	int		error;
	int		tube;
	int		start_end;
	int		begin_tube;
	char	*name_start;
	char	*name_end;
	char	*baseline;
	t_room	*start;
	t_room	*end;
}					t_basis;

#endif
