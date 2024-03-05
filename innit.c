/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:33:19 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/04 01:36:29 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_assign(t_data *data, int ph_pos)
{
	t_philo	*ph;
	t_fork	*forks;
	int		n_philo;

	ph = data->philos + ph_pos;
	forks = data->forks;
	n_philo = data->n_philo;
	if (ph->id % 2 == 0)
	{
		ph->left_fork = &forks[(ph_pos + 1) % n_philo]; 
		ph->right_fork = &forks[ph_pos + 1]; 
	}
	else
	{
		ph->left_fork = &forks[ph_pos + 1]; 
		ph->right_fork = &forks[(ph_pos + 1) % n_philo]; 
	}
}

void	innit_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].info = data;
		data->philos[i].eat_counter = 0;
		data->philos[i].is_full = false;
		mutex_call(&data->forks[i].fork, data, INNIT, i);
		mutex_call(&data->philos[i].philo_safety, data, INNIT, i);
		data->forks[i].fork_id = i;
		forks_assign(data, i);
		i++;
	}
}

void	innit_data(t_data *i)
{
	int	n;

	i->philos = (t_philo *)malloc(sizeof(t_philo) * i->n_philo);
	if (!i->philos)
		out(2);
	i->forks = (t_fork *)malloc(sizeof(t_fork) * i->n_philo);
	if (!i->forks)
		(free(i->philos), out(2));
	if (pthread_mutex_init(&i->data_safety, NULL) != 0
		|| pthread_mutex_init(&i->cus_prnt, NULL) != 0)
		(free_it(i, false, -1), out(2));
	i->all_philos_ready = false;
	i->end_of_life = false;
	innit_philos(i);
}
