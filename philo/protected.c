/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:42:56 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/18 07:29:44 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex(pthread_mutex_t *mtx, t_data *data,
		t_emtx call, bool *ready)
{
	if (call == INNIT)
	{
		if (pthread_mutex_init(mtx, NULL) != 0)
			out(2, data);
		else
			*ready = true;
	}
	else if (call == LOCK)
		pthread_mutex_lock(mtx);
	else if (call == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (call == DESTROY && *ready == true)
	{
		set_bool(data, ready, false);
		pthread_mutex_destroy(mtx);
	}
}

bool	get_bool(t_data *data, bool *access)
{
	bool	ret;

	ft_mutex(&data->safe_access, data, LOCK, &data->ready);
	ret = *access;
	ft_mutex(&data->safe_access, data, UNLOCK, &data->ready);
	return (ret);
}

void	set_bool(t_data *data, bool *access, bool target)
{
	ft_mutex(&data->safe_access, data, LOCK, &data->ready);
	*access = target;
	ft_mutex(&data->safe_access, data, UNLOCK, &data->ready);
}

long	get_long(t_data *data, long *access)
{
	long	ret;

	ft_mutex(&data->safe_access, data, LOCK, &data->ready);
	ret = *access;
	ft_mutex(&data->safe_access, data, UNLOCK, &data->ready);
	return (ret);
}

void	set_long(t_data *data, long *access, long target)
{
	ft_mutex(&data->safe_access, data, LOCK, &data->ready);
	*access = target;
	ft_mutex(&data->safe_access, data, UNLOCK, &data->ready);
}
