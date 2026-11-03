/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:47:03 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 10:37:25 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_routine(t_philo *philo)
{
	while (!stop(philo->data))
	{
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (stop(philo->data))
			break ;
		write_lock("is thinking", philo);
		if (philo->data->nb_philo % 2 == 1)
			usleep((philo->data->time_to_eat / 2) * 1000);
		if (stop(philo->data))
			break ;
		write_lock("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->nb_philo == 1)
		return (philo_alone(philo), NULL);
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	philo_routine(philo);
	return (NULL);
}

void	clean_threads(t_data *data, int i)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
	while (--i >= 0)
		pthread_join(data->philos[i].thread, NULL);
	free_all(data);
}

int	setup_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher,
				&data->philos[i]))
			return (clean_threads(data, i), 1);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (clean_threads(data, i), 1);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Pthread join Error\n"), 1);
	}
	if (pthread_join(monitor, NULL))
		return (printf("Pthread join Error\n"), 1);
	return (0);
}
