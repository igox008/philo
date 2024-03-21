/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 04:41:49 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/20 20:16:37 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	n_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*num;

	i = 0;
	len = n_len(n);
	num = (char *)malloc(len + 1);
	if (num == NULL)
		return (NULL);
	num[len] = '\0';
	while (len - 1 >= i)
	{
		num[len - 1] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (num);
}

char	*get_philo_sem(int id)
{
	char	*ret;
	char	*n;
	int		i;
	int		j;

	i = -1;
	n = ft_itoa(id);
	if (!n)
		return (NULL);
	ret = (char *)malloc(ft_strlen("/philo_n_") + ft_strlen(n) + 1);
	if (!ret)
		return (free(n), NULL);
	while ("/philo_n_"[++i])
		ret[i] = "/philo_n_"[i];
	j = 0;
	while (n[j])
	{
		ret[i] = n[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (free(n), ret);
}

void	innit_philo(t_data *data)
{
	int		i;
	char	*s;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].times_eat = 0;
		data->philos[i].is_full = false;
		s = get_philo_sem(i + 1);
		if (!s)
			out(1, data, -2);
		sem_unlink((const char *)s);
		data->philos[i].safe_philo = get_sem(data, s, 1);
		data->philos[i].name = s;
		data->philos[i].last_eat = get_msec();
		i++;
	}
}

void	innit_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		exit(2);
	null_it(data);
	sem_unlink("/safe_write");
	sem_unlink("/forks");
	data->safe_write = get_sem(data, "/safe_write", 1);
	data->forks = get_sem(data, "/forks", data->n_philo);
	innit_philo(data);
}
