/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_weak_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:39:21 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:12:25 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline t_byte	lemin_free_split(char **split)
{
	ssize_t size;

	size = -1;
	if (!split)
		return (1);
	while (split[++size])
		free(split[size]);
	free(split);
	return (0);
}
