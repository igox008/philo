/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 02:57:17 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/19 06:16:28 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	is_all_full(t_data *data)
{
	int	i;
	int	eat;

	(1) && (i = 0, eat = 0);
	while (i < data->n_philo)
	{
		if (get_bool(data, &data->philos[i].is_full))
			eat++;
		i++;
	}
	if (eat == data->n_philo)
		return (true);
	return (false);
}

void	*monitor_philos(void *dt)
{
	t_data	*data;
	int		i;

	data = (t_data *)dt;
	while (!get_bool(data, &data->all_philos_ready))
		;
	ft_usleep(data->t_2_die / 2);
	while (!get_bool(data, &data->sim_finish))
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (is_dead(&data->philos[i], data)
				&& !get_bool(data, &data->sim_finish))
			{
				set_bool(data, &data->sim_finish, true);
				custom_printf(DIED, data, data->philos[i].id);
			}
			i++;
		}
		if (is_all_full(data))
			break ;
	}
	return (NULL);
}
