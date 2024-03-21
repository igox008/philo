/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:23:55 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/18 07:10:55 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		ph;
	bool		innit;
	int			i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	innit = false;
	parse_it(ac, av, &ph, &innit);
	if (!innit)
		return (1);
	innit = false;
	innit_data(&ph, &innit);
	if (!innit)
		return (1);
	ph.stamp = get_msec();
	if (simulation_engine(&ph))
		return (free(ph.philos), free(ph.forks), 1);
	return (free(ph.philos), free(ph.forks), 0);
}
