/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:22:59 by idemchen          #+#    #+#             */
/*   Updated: 2017/07/10 18:22:18 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if ((s2 = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(s2, s1, len + 1);
	return (s2);
}
