/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 22:45:30 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 17:58:16 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned	lemin_check_integer(char *str)
{
	unsigned	counter;

	counter = 0;
	while (SPACED(*str) || TABBED(*str))
		(++counter) && (str++);
	if (!DIGIT(*str) && (counter == ft_strlen(str) || !*str))
		return (1);
	return (0);
}

int				lemin_atoi(char *str)
{
	char	sign;
	long	nbr;

	sign = 1;
	while (SPACED(*str) || TABBED(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	nbr = 0;
	while (*str >= 48 && *str <= 57)
		(nbr = nbr * 10 + *str++ - 48);
	if (!lemin_check_integer(str)
		|| !(sign * nbr <= 2147483647 && sign * nbr >= -2147483648))
		return (-1);
	return (sign * nbr);
}
