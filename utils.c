/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/20 10:04:55 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long long	get_time(void)
{
	struct timeval	t;
	long long		ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
