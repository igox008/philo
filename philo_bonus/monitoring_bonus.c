/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 02:57:17 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 07:22:48 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_dead(t_philo *philo, t_data *data)
{
	long	delay;

	sem_wait(philo->safe_philo);
	if (philo->is_full)
	{
		sem_post(philo->safe_philo);
		return (false);
	}
	delay = get_msec() - philo->last_eat;
	sem_post(philo->safe_philo);
	if (delay > data->t_2_die)
		return (true);
	return (false);
}

void	*monitor_philos(void *dt)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)dt;
	data = philo->data;
	ft_usleep(data->t_2_die / 2);
	while (1)
	{
		if (is_dead(philo, data))
		{
			custom_printf(DIED, data, philo->id);
			exit(1);
		}
	}
	return (NULL);
}
