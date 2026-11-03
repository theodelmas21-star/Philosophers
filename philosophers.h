/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:38:24 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:39 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	int					r_fork;
	int					l_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	size_t				start_time;
	pthread_mutex_t		forks_lock;
	t_philo				*philos;
	int					*forks_tab;
	int					nb_meal;
	int					nb_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
}						t_data;

long long				ft_atoi(const char *nptr);
int						parser(int ac, char **av, t_data *data);
long long				ft_isnum(const char *str);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds);
void					write_lock(char *str, t_philo *philos);
void					free_forks(t_data *data, int res);
void					free_mutex(t_data *data, int res);
int						init_data(t_data *data);
int						setup_threads(t_data *data);
void					free_all(t_data *data);
void					philo_alone(t_philo *philo);
void					philo_routine(t_philo *philo);
int						all_eat(t_data *data);
void					*monitor_routine(void *data);
int						stop(t_data *data);
int						take_forks(t_philo *philo);
int						eat(t_philo *philo);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

#endif