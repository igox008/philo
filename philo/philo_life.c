/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 06:30:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/14 21:31:28 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	custom_printf(THINKING, philo->data, philo->id);
}

void	lock_forks(t_philo *philo, t_data *data)
{
	ft_mutex(&philo->right_fork->fork, data, LOCK, &philo->ready);
	custom_printf(TAKE_FORK, data, philo->id);
	if (data->n_philo > 1)
	{
		ft_mutex(&philo->left_fork->fork, data, LOCK, &philo->ready);
		custom_printf(TAKE_FORK, data, philo->id);
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	lock_forks(philo, data);
	set_long(data, &philo->last_eat, get_msec());
	if (data->n_philo > 1)
		philo->times_eat++;
	if (data->n_philo > 1)
		custom_printf(EATING, data, philo->id);
	ft_usleep(data->t_2_eat);
	if (data->n_eat > 0 && philo->times_eat == data->n_eat)
		set_bool(data, &philo->is_full, true);
	ft_mutex(&philo->right_fork->fork, data, UNLOCK, &philo->ready);
	if (data->n_philo > 1)
		ft_mutex(&philo->left_fork->fork, data, UNLOCK, &philo->ready);
}

void	*philo_life(void *ph)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ph;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(data->t_2_eat);
	while (!get_bool(data, &data->sim_finish))
	{
		if (get_bool(data, &philo->is_full))
			break ;
		eat(philo);
		if (data->n_philo > 1)
		{
			custom_printf(SLEEPING, data, philo->id);
			ft_usleep(data->t_2_sleep);
			think(philo);
		}
		else
			ft_usleep(data->t_2_die);
	}
	return (NULL);
}

void	simulation_engine(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_eat == 0)
		return ;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].philo, NULL,
				philo_life, &data->philos[i]) != 0)
			out(2, data);
		i++;
	}
	set_bool(data, &data->all_philos_ready, true);
	if (pthread_create(&data->monitor, NULL,
			monitor_philos, (void *)data) != 0)
			out(2, data);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			out(2, data);
		i++;
	}
	set_bool(data, &data->sim_finish, true);
	(pthread_join(data->monitor, NULL) != 0) && (out(2, data));
}
