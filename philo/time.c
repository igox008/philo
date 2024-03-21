/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:46:58 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:18:36 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_msec(void)
{
	struct timeval	t;
	long			ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(long msec)
{
	long	target_time;

	target_time = get_msec() + msec;
	while (get_msec() < target_time)
	{
		usleep(500);
	}
}
