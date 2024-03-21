/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:47 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/19 05:49:15 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_all_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	check_arg(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (*str && *str == ' ')
		str++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (i > 0 && !(str[i] >= '0' && str[i] <= '9')
			&& !is_all_spaces(str + i))
			return (0);
		else if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '+')
			return (0);
		if (str[i] >= '0' && str[i] <= '9')
			c++;
		i++;
	}
	if (!c)
		return (0);
	return (1);
}

void	get_res(char *s, t_data *p)
{
	static int	i;

	if (!i)
		p->n_philo = ft_atoi(s);
	else if (i == 1)
		p->t_2_die = ft_atoi(s);
	else if (i == 2)
		p->t_2_eat = ft_atoi(s);
	else if (i == 3)
		p->t_2_sleep = ft_atoi(s);
	else if (i == 4)
		p->n_eat = ft_atoi(s);
	i++;
}

void	parse_it(int ac, char **av, t_data *p, bool *innit)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!check_arg(av[i]))
			return ;
		get_res(av[i], p);
		i++;
	}
	if (p->n_philo < 0 || p->t_2_die < 60 || p->t_2_eat < 60
		|| p->t_2_sleep < 60)
		return ;
	if (ac == 5)
		p->n_eat = -1;
	else if (p->n_eat < 0)
		return ;
	*innit = true;
}
