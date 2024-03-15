/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:23:55 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/10 11:07:18 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data		ph;
	int			i;

	i = 0;
	parse_it(ac, av, &ph);
	innit_data(&ph);
	ph.stamp = get_msec();
	simulation_engine(&ph);
}
