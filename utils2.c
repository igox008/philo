/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:45:58 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/03 22:31:07 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_bool(pthread_mutex_t *mtx, t_data *data, bool *org, bool val)
{
	mutex_call(mtx, data, LOCK, data->n_philo);
	*org = val;
	mutex_call(mtx, data, LOCK, data->n_philo);
}

long	get_usec(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) != 0)
		return (-1);
	return ((t.tv_sec * 1000000) + t.tv_usec);
}

void	ft_usleep(long usec)
{
	long	start_time;
	long	target_time;
	long	curr_time;
	long	rem_time;

	start_time = get_usec();
	if (start_time == -1)
		return ;
	target_time = start_time + usec;
	curr_time = get_usec();
	while (curr_time != -1 && curr_time < target_time)
	{
		rem_time = (target_time - curr_time) / 2;
		if (rem_time > 1000 )
		{
			if (usleep(rem_time) == -1)
				return ;
		}
		curr_time = get_time();
	}
}
