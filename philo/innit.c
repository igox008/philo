/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:41:49 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:04:34 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	innit_forks(t_philo *philo, t_data *data, int i)
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

void	innit_to_false(t_data *data)
{
	int	i;

	i = 0;
	data->wrt = false;
	data->acss = false;
	data->all_philos_ready = false;
	data->sim_finish = false;
	data->free_it = false;
	data->ready = false;
	while (i < data->n_philo)
	{
		data->forks[i].ready = false;
		data->philos[i].ready = false;
		i++;
	}
}

void	innit_philo(t_data *data, bool *try)
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
		data->forks[i].fork_id = i;
		ft_mutex(&data->forks[i].fork, data, INNIT,
			&data->forks[i].ready);
		if (!data->forks[i].ready)
			return ;
		ft_mutex(&data->philos[i].safe_philo, data, INNIT,
			&data->philos[i].ready);
		if (!data->philos[i].ready)
			return ;
		innit_forks(&data->philos[i], data, i);
		i++;
	}
	*try = true;
}

void	innit_data(t_data *data, bool *innit)
{
	int		i;
	bool	try;

	(1) && (i = 0, try = false);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return ;
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->n_philo);
	if (!data->forks)
	{
		free(data->philos);
		data->philos = NULL;
		return ;
	}
	innit_to_false(data);
	ft_mutex(&data->safe_write, data, INNIT, &data->wrt);
	if (!data->wrt)
		return ;
	ft_mutex(&data->safe_access, data, INNIT, &data->acss);
	if (!data->wrt)
		return ;
	innit_philo(data, &try);
	if (!try)
		return ;
	*innit = true;
}
