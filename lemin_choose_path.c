/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_choose_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 17:31:48 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 17:58:52 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool	lemin_make_a_move(t_hole *from, t_hole *to)
{
	if (!from->ants || to->ants)
		return (0);
	to->ants = from->ants;
	from->ants = 0;
	write(1, (to->ants % 12 >= 6) ? "L\x1B[0;3" : "L\x1B[1;3", 6);
	ft_putnbr(to->ants % 6 + 1);
	write(1, "m", 1);
	ft_putnbr(to->ants);
	write(1, "\x1B[0m-", 5);
	ft_putstr(to->name);
	write(1, " ", 1);
	(from->gate == 's') ?
		from->ants = to->ants + 1 : 0;
	(to->gate == 'e') ?
		to->ants = 0 : 0;
	return (1);
}
