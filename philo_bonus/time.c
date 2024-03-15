/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:46:58 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/14 20:32:46 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_usec(void)
{
	struct timeval	t;
	long			us;

	gettimeofday(&t, NULL);
	us = (t.tv_sec * 1000000) + (t.tv_usec);
	return (us);
}

long	get_msec(void)
{
	struct timeval	t;
	long			ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long usec)
{
	long	start_time;
	long	target_time;
	long	curr_time;
	long	rem_time;

	start_time = get_msec();
	if (start_time == -1)
		return ;
	target_time = start_time + usec;
	curr_time = get_msec();
	while (curr_time != -1 && curr_time < target_time)
	{
		rem_time = (target_time - curr_time) / 2;
		if (rem_time > 1)
			usleep(rem_time * 1000);
		curr_time = get_msec();
	}
}
