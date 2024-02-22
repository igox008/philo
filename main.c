/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:23:55 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/20 10:37:03 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data		ph;
	// pthread_t	pt;
	int			i;

	i = 0;
	parse_it(ac, av, &ph);
	innit_data(&ph);
	while (i < ph.n_philo)
	{
		
		i++;
	}
}
