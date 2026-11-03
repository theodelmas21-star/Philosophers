/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:46:07 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:30 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_eat(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	if (data->nb_meal == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meal)
			done = 0;
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	if (done == 1)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
	}
	return (done);
}

int	is_dead(t_philo *philo)
{
	long	cur_time;

	cur_time = get_current_time();
	pthread_mutex_lock(&philo->data->meal_lock);
	if (cur_time - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		pthread_mutex_lock(&philo->data->dead_lock);
		write_lock("died", philo);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

void	*monitor_routine(void *da)
{
	int		i;
	t_data	*data;

	data = (t_data *)da;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (all_eat(data))
			return (NULL);
		ft_usleep(2);
	}
	return (NULL);
}
