/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 06:30:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/15 08:16:25 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	think(t_philo *philo)
{
	custom_printf(THINKING, philo->data, philo->id);
}

void	lock_forks(t_philo *philo, t_data *data)
{
	ft_sem(data->forks, data, WAIT, NULL, 0);
	custom_printf(TAKE_FORK, data, philo->id);
	if (data->n_philo > 1)
	{
		ft_sem(data->forks, data, WAIT, NULL, 0);
		custom_printf(TAKE_FORK, data, philo->id);
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	lock_forks(philo, data);
	set_long(data, &philo->last_eat, get_msec());
	philo->times_eat++;
	if (data->n_philo > 1)
		custom_printf(EATING, data, philo->id);
	ft_usleep(data->t_2_eat);
	if (data->n_eat > 0 && philo->times_eat == data->n_eat)
		set_bool(data, &philo->is_full, true);
	ft_sem(data->forks, data, POST, NULL, 0);
	if (data->n_philo > 1)
		ft_sem(data->forks, data, POST, NULL, 0);;
}

void	*philo_life(void *ph)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)ph;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(data->t_2_eat);
	pthread_create(&philo->monitor, NULL, monitor_philos, philo);
	while (1)
	{
		if (get_bool(data, &philo->is_full))
			exit(0);
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
	pthread_join(philo->monitor, NULL);
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
			;// HANDLE FORK ERROR
		else if (!pid)
		{
			philo_life(&data->philos[i]);
			exit(0);
		}
		else if (pid > 0)
			data->philos[i].pid = pid;
		i++;
	}
	// printf("test\n");
	wait_childs(data);
}
