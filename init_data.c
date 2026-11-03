/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:53:23 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:15 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks_tab = malloc(sizeof(int) * data->nb_philo);
	if (!data->forks_tab)
		return ;
	while (i < data->nb_philo)
	{
		data->forks_tab[i] = 0;
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return ;
	while (i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].r_fork = (i + 1) % data->nb_philo;
		data->philos[i].l_fork = i;
		i++;
	}
}

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (free_mutex(data, 1), free(data), 1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (free_mutex(data, 2), free(data), 1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (free_mutex(data, 3), free(data), 1);
	if (pthread_mutex_init(&data->forks_lock, NULL) != 0)
		return (free_mutex(data, 4), free(data), 1);
	data->dead_flag = 0;
	data->start_time = get_current_time();
	init_forks(data);
	if (!data->forks_tab)
		return (free_mutex(data, 5), free(data), 1);
	init_philos(data);
	if (!data->philos)
	{
		free(data->forks_tab);
		return (free_mutex(data, 5), free(data), 1);
	}
	return (0);
}
