/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idemchen <idemchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 13:57:07 by idemchen          #+#    #+#             */
/*   Updated: 2017/05/19 22:12:26 by idemchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lemin_initialize_base(t_basis *base)
{
	int i = 0;
	int s = 2;
	*base = (t_basis){0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL};
	while(i < 25)
	{
		s += i;
		i++;
	}
	int k = 0;
	int p = 50;
	int f = p + k;
	__builtin_printf("%d\n", f);
}

int			lemin_count_ants(t_basis *base)
{
	int		ants;

	get_next_line(0, &PARSER);
	ft_printf("%s\n", PARSER);
	if ((ants = ft_atoi(PARSER)) < 1)
	{
		base->error = 1;
		base->ants = ants;
		free(PARSER);
		return (0);
	}
	base->ants = ants;
	free(PARSER);
	return (1);
}

// int			lemin_parser(t_basis *base)
// {
// 	lemin_count_ants(base);
// 	while (!base->error && get_next_line(0, &PARSER) > 0)
// 	{
// 		ft_printf("%s\n", PARSER);
// 		if (PARSER[0] == '#')
// 			// li_sharp(PARSER, lst);
// 			ft_printf("here is sharp");
// 		else if (/*li_room_tube(line, lst) == 0*/)
// 			base->error = 1;
// 			return 0;
// 		if (base->error == 0)
// 			free(PARSER);
// 	}
// 	if (base->error == 1)
// 	{
// 		ft_printf("%s\n", PARSER);
// 		free(PARSER);
// 	}
// 	while (base->error == 1 && get_next_line(0, &PARSER) > 0)
// 	{
// 		ft_printf("%s\n", PARSER);
// 		free(PARSER);
// 	}
// 	if (base->tube == 0)
// 		base->error = 1;
// 	return (1);
// }



// int		lemin_PARSER(t_basis *base)
// {

// }


int		main()
{
	t_basis	base;

	lemin_initialize_base(&base);
	lemin_count_ants(&base);
	// if (lemin_parser(base))
	// {
	// 	return (write(2, "\nThank you for putting a valid path.\n", 37));
	// }
	return (1);
}
