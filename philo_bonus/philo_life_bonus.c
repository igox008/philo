/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 06:30:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 07:34:12 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	custom_printf(THINKING, philo->data, philo->id);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	custom_printf(TAKE_FORK, data, philo->id);
	sem_wait(data->forks);
	custom_printf(TAKE_FORK, data, philo->id);
	philo->times_eat++;
	sem_wait(philo->safe_philo);
	philo->last_eat = get_msec();
	if (data->n_eat > 0 && philo->times_eat == data->n_eat)
		philo->is_full = true;
	sem_post(philo->safe_philo);
	if (data->n_philo > 1)
		custom_printf(EATING, data, philo->id);
	ft_usleep(data->t_2_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*philo_life(void *ph)
{
	t_philo	*philo;
	t_data	*data;

	(1) && (philo = (t_philo *)ph, data = philo->data);
	if (philo->id % 2 == 0)
		ft_usleep(data->t_2_eat);
	if (pthread_create(&philo->monitor, NULL, monitor_philos, philo) != 0)
		out(1, data, philo->pid);
	while (1)
	{
		eat(philo);
		if (data->n_philo > 1)
		{
			custom_printf(SLEEPING, data, philo->id);
			ft_usleep(data->t_2_sleep);
			custom_printf(THINKING, philo->data, philo->id);
		}
		else
			ft_usleep(data->t_2_die);
		sem_wait(philo->safe_philo);
		(philo->is_full) && (out(0, data, philo->pid));
		sem_post(philo->safe_philo);
	}
	(pthread_join(philo->monitor, NULL) != 0) && (out(1, data, philo->pid));
	return (NULL);
}

void	simulation_engine(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	if (data->n_eat == 0)
		return ;
	while (i < data->n_philo)
	{
		pid = fork();
		if (pid == -1)
			out(1, data, -1);
		else if (!pid)
		{
			philo_life(&data->philos[i]);
			exit(0);
		}
		else if (pid > 0)
			data->philos[i].pid = pid;
		i++;
	}
	wait_childs(data);
}
