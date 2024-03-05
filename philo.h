/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:06 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/04 01:38:30 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define LOCK 0
# define UNLOCK 1
# define INNIT 2
# define TAKEN_FORK 3
# define EATEN 4
# define SLEEPING 5
# define THINKING 6
# define DIED 7

typedef struct s_data	t_data;

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct	s_philo
{
	bool			is_full;
	long			last_eat;
	int				id;
	int				eat_counter;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	philo_safety;
	t_data			*info;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_2_die;
	int				t_2_eat;
	int				t_2_sleep;
	int				n_eat;
	t_fork			*forks;
	t_philo			*philos;
	bool			all_philos_ready;
	bool			end_of_life;
	long			stamp;
	pthread_mutex_t	data_safety; // protect accessing to data
	pthread_mutex_t	cus_prnt;
}	t_data;

void		parse_it(int ac, char **av, t_data *p);
void		innit_data(t_data *i);
long		get_time(void);
void		out(int status);
void		free_it(t_data *data, bool mtx_destroy, int n);
void		mutex_call(pthread_mutex_t *mtx, t_data *data, int call, int n);
void		ft_usleep(long usec);
long		get_usec(void);
void		custom_printf(int status, t_data *data, int id);
void		assign_bool(pthread_mutex_t *mtx, t_data *data, bool *org, bool val);

#endif