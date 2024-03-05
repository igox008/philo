/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:22:45 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/04 01:41:14 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_bool(t_data *data, bool check)
{
	bool	ret;

	mutex_call(&data->data_safety, data, LOCK, data->n_philo);
	ret = check;
	mutex_call(&data->data_safety, data, UNLOCK, data->n_philo);
	return (ret);
}

void	eat(t_philo *philo)
{
	mutex_call(&philo->left_fork->fork, philo->info, LOCK, philo->info->n_philo);
	custom_printf(TAKEN_FORK, philo->info, philo->id);
	mutex_call(&philo->right_fork->fork, philo->info, LOCK, philo->info->n_philo);
	custom_printf(TAKEN_FORK, philo->info, philo->id);
	mutex_call(&philo->philo_safety, philo->info, LOCK, philo->info->n_philo);
	philo->last_eat = get_time();
	mutex_call(&philo->philo_safety, philo->info, UNLOCK, philo->info->n_philo);
	philo->eat_counter++;
	custom_printf(EATEN, philo->info, philo->id);
	ft_usleep(philo->info->t_2_eat);
	if (philo->info->n_eat > 0 && philo->eat_counter == philo->info->n_eat)
		assign_bool(&philo->philo_safety, philo->info, &philo->is_full, true);
	mutex_call(&philo->right_fork->fork, philo->info, UNLOCK, philo->info->n_philo);
	mutex_call(&philo->left_fork->fork, philo->info, UNLOCK, philo->info->n_philo);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_bool(philo->info, philo->info->all_philos_ready))
		;
	while (!check_bool(philo->info, philo->info->end_of_life))
	{
		if (!check_bool(philo->info, philo->is_full))
			break ;
		// eating ?
		custom_printf(SLEEPING, philo->info, philo->id);
		ft_usleep(philo->info->t_2_sleep);
	}
	return (NULL);
}

void	simulation_starter(t_data *data)
{
	int	i;

	i = 0;
	if (!data->n_eat)
		return ;
	else if (data->n_philo == 1)
		;// handle one philo case
	else
	{
		while (i < data->n_philo)
		{
			if (pthread_create(&data->philos[i].philo, NULL, philo_life, &data->philos[i]) != 0)
				(free_it(data, true, data->n_philo), out(2));
			i++;
		}
	}
	mutex_call(&data->data_safety, data, LOCK, data->n_philo);
	data->all_philos_ready = true;
	data->stamp = get_time();
	mutex_call(&data->data_safety, data, UNLOCK, data->n_philo);
}
