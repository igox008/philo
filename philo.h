/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:06 by alaassir          #+#    #+#             */
/*   Updated: 2024/02/22 13:42:02 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct	s_philo
{
	bool			is_finish;
	long long		last_eat;
	int				id;
	int				n_eat;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	// pthread_mutex_t	*checker; //--> needeed lately
	t_data			*info;
}	t_philo;

typedef struct s_data
{
	int			n_philo;
	int			t_2_die;
	int			t_2_eat;
	int			t_2_sleep;
	int			n_eat;
	long long	(*time)(void);
	t_fork		*forks;
	t_philo		*philos;
}	t_data;

void	parse_it(int ac, char **av, t_data *p);
void	innit_data(t_data *i);
long long	get_time(void);

#endif