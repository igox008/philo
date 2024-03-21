/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:00:13 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:06:44 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	out(int status, t_data *data)
{
	int	i;

	i = 0;
	set_bool(data, &data->sim_finish, true);
	while (i < data->n_philo)
	{
		if (data->forks[i].ready)
			ft_mutex(&data->forks[i].fork, data, DESTROY,
				&data->forks[i].ready);
		if (data->philos[i].ready)
			ft_mutex(&data->philos[i].safe_philo, data,
				DESTROY, &data->forks[i].ready);
		i++;
	}
	if (data->wrt)
		ft_mutex(&data->safe_access, data, DESTROY, &data->wrt);
	if (data->acss)
		ft_mutex(&data->safe_write, data, DESTROY, &data->acss);
	if (status == 2)
		(free(data->forks), free(data->philos));
	return (status);
}

void	custom_printf(t_ephilo status, t_data *data, int id)
{
	long		t;

	ft_mutex(&data->safe_write, data, LOCK, &data->ready);
	t = get_msec() - data->stamp;
	if (status == TAKE_FORK && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d has taken a fork\n", t, id);
	else if (status == EATING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is eating\n", t, id);
	else if (status == SLEEPING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is sleeping\n", t, id);
	else if (status == THINKING && !get_bool(data, &data->sim_finish))
		printf("%ld\t%d is thinking\n", t, id);
	else if (status == DIED)
		printf("%ld\t%d died\n", t, id);
	ft_mutex(&data->safe_write, data, UNLOCK, &data->ready);
}

long	ft_atoi(char *str)
{
	int		i;
	int		s;
	long	rsl;

	(1) && (i = 0, s = 1, rsl = 0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (((rsl * 10) + (str[i] - 48) * s > 2147483647
				|| (rsl * 10) + (str[i] - 48) * s < -2147483648))
			return (-2147483649);
		rsl = (rsl * 10) + (str[i] - 48);
		i++;
	}
	return (rsl * s);
}
