/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:41:49 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/10 11:06:25 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	innit_forks(t_philo *philo, t_data *data, int i) // in mutex_lock use even odd way to prevent Deadlock
{
	philo->right_fork = &data->forks[i];
	if (data->n_philo > 1)
	{
		if (philo->data->n_philo == i + 1)
			philo->left_fork = &data->forks[0];
		else
			philo->left_fork = &data->forks[i + 1];
	}
}

void	innit_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = get_msec();
		data->philos[i].data = data;
		data->philos[i].times_eat = 0;
		data->philos[i].is_full = false;
		data->forks[i].ready = false;
		data->forks[i].fork_id = i;
		ft_mutex(&data->forks[i].fork, data, INNIT,
			&data->forks[i].ready);
		ft_mutex(&data->philos[i].safe_philo, data, INNIT,
			&data->philos[i].ready);
		innit_forks(&data->philos[i], data, i);
		i++;
	}
}

void	innit_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		exit(2);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->n_philo);
	if (!data->forks)
		(free(data->philos), exit(2));
	data->wrt = false;
	data->acss = false;
	ft_mutex(&data->safe_write, data, INNIT, &data->ready);
	ft_mutex(&data->safe_access, data, INNIT, &data->ready);
	data->all_philos_ready = false;
	data->sim_finish = false;
	innit_philo(data);
}
