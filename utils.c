/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/03 19:44:15 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	get_time(void)
{
	struct timeval	t;
	long			ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void	free_it(t_data *data, bool mtx_destroy, int n)
{
	int	i;

	i = 0;
	if (mtx_destroy)
	{
		while (i < n)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	free(data->philos);
	free(data->forks);
}

void	out(int status)
{
	if (status != 0)
		printf("Error\n");
	exit(status);
}

void	mutex_call(pthread_mutex_t *mtx, t_data *data, int call, int n)
{
	if (call == INNIT)
	{
		if (pthread_mutex_init(mtx, NULL) != NULL)
			(free_it(data, true, n), out(2));
	}
	else if (call == LOCK)
	{
		if (pthread_mutex_lock(mtx) != 0)
			(free_it(data, true, n), out(2));
	}
	else if (call == UNLOCK)
	{
		if (pthread_mutex_unlock(mtx) != 0)
			(free_it(data, true, n), out(2));
	}
}

void	custom_printf(int status, t_data *data, int id)
{
	long	t;

	mutex_call(&data->cus_prnt, data, LOCK, data->n_philo);
	t = get_time() - data->stamp;
	if (status == TAKEN_FORK)
		printf("%ld\t%d has taken a fork\n", t, id);
	else if (status == EATEN)
		printf("%ld\t%d is eating\n", t, id);
	else if (status == SLEEPING)
		printf("%ld\t%d is sleeping\n", t, id);
	else if (status == THINKING)
		printf("%ld\t%d is thinking\n", t, id);
	else if (status == DIED)
		printf("%ld\t%d died", t, id);
	mutex_call(&data->cus_prnt, data, UNLOCK, data->n_philo);
}
