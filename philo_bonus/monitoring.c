/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 02:57:17 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/15 08:03:54 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_dead(t_philo *philo, t_data *data)
{
	long	delay;

	if (get_bool(data, &philo->is_full))
		return (false);
	delay = get_msec() - get_long(data, &philo->last_eat);
	if (delay > data->t_2_die)
		return (true);
	return (false);
}

void	*monitor_philos(void *dt)
{
	t_data	*data;
	t_philo	*philo;
	// int		i;

	philo = (t_philo *)dt;
	data = philo->data;
	ft_usleep(data->t_2_die / 2);
	while (1)
	{
		if (is_dead(philo, data))
		{
			custom_printf(DIED, data, philo->id);
			exit(0);
		}
	}
	return (NULL);
}
