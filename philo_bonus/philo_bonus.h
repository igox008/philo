/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:06 by alaassir          #+#    #+#             */
/*   Updated: 2024/03/10 10:58:15 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

// Reset
#define RST "\033[0m"

// Regular colors
#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"

// Bold colors
#define B_BLK "\033[1;30m"
#define B_RED "\033[1;31m"
#define B_GRN "\033[1;32m"
#define B_YEL "\033[1;33m"
#define B_BLU "\033[1;34m"
#define B_MAG "\033[1;35m"
#define B_CYN "\033[1;36m"
#define B_WHT "\033[1;37m"

// Background colors
#define BG_BLK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GRN "\033[42m"
#define BG_YEL "\033[43m"
#define BG_BLU "\033[44m"
#define BG_MAG "\033[45m"
#define BG_CYN "\033[46m"
#define BG_WHT "\033[47m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	bool			is_full;
	long			last_eat;
	long			id;
	long			times_eat;
	pid_t			pid;
	t_data			*data;
	sem_t			*safe_philo;
	bool			ready;
	char			*name;
	pthread_t		monitor;
}	t_philo;

typedef struct s_data
{
	long			n_philo;
	long			t_2_die;
	long			t_2_eat;
	long			t_2_sleep;
	long			n_eat;
	long			stamp;
	sem_t			*safe_write;
	bool			wrt;
	sem_t			*safe_access;
	bool			acss;
	sem_t			*forks;
	t_philo			*philos;
	bool			ready;
}	t_data;

typedef enum s_sem
{
	OPEN,
	POST,
	WAIT,
	CLOSE,
	UNLINK
}	t_sem;

typedef enum s_ephilo
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FORK,
	DIED
}	t_ephilo;

void	parse_it(int ac, char **av, t_data *p);
void	innit_data(t_data *i);
long	get_usec(void);
long	get_msec(void);
void	ft_sem(sem_t *sem, t_data *data, t_sem call, char *s, int innit);
int		out(int status, t_data *data);
void	ft_usleep(long usec);
bool	get_bool(t_data *data, bool *access);
void	set_bool(t_data *data, bool *access, bool target);
long	get_long(t_data *data, long *access);
void	set_long(t_data *data, long *access, long target);
void	custom_printf(t_ephilo status, t_data *data, int id);
void	simulation_engine(t_data *data);
void	*monitor_philos(void *dt);
int		ft_strlen(char *s);
void	wait_childs(t_data *data);
void	null_it(t_data *data);
void	kill_childs(t_data *data);

#endif