/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:23:55 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/15 07:52:00 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	null_it(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philos[i].name = NULL;
		data->philos[i].pid = -1;
	}
}

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
