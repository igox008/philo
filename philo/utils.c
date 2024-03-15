/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/10 10:59:45 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	out(int status, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (!data->forks[i].ready)
			continue ;
		else
		{
			ft_mutex(&data->forks[i].fork, data, DESTROY,
				&data->forks[i].ready);
			ft_mutex(&data->philos[i].safe_philo, data,
				DESTROY, &data->forks[i].ready);
		}
		i++;
	}
	ft_mutex(&data->safe_access, data, DESTROY, &data->wrt);
	ft_mutex(&data->safe_write, data, DESTROY, &data->acss);
	(free(data->philos), free(data->forks), exit(status));
	return (1);
}

void	custom_printf(t_ephilo status, t_data *data, int id)
{
	long		t;

	ft_mutex(&data->safe_write, data, LOCK, &data->ready);
	t = get_msec() - data->stamp;
	if (status == TAKE_FORK && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d has taken a fork\n", t, id);
	else if (status == EATING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is eating\n", t, id);
	else if (status == SLEEPING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is sleeping\n", t, id);
	else if (status == THINKING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is thinking\n", t, id);
	else if (status == DIED)
		printf("%ld\t%d died\n", t, id);
	ft_mutex(&data->safe_write, data, UNLOCK, &data->ready);
}
