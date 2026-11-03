/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:46:11 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:23 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_alone(t_philo *philo)
{
	ft_usleep(philo->data->time_to_die);
}

int	stop(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int	take_forks(t_philo *philo)
{
	while (1)
	{
		if (stop(philo->data))
			return (0);
		pthread_mutex_lock(&philo->data->forks_lock);
		if (philo->data->forks_tab[philo->l_fork] == 0
			&& philo->data->forks_tab[philo->r_fork] == 0)
		{
			philo->data->forks_tab[philo->l_fork] = 1;
			philo->data->forks_tab[philo->r_fork] = 1;
			pthread_mutex_unlock(&philo->data->forks_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->forks_lock);
		ft_usleep(1);
	}
	if (stop(philo->data))
		return (0);
	write_lock("has taken a fork", philo);
	write_lock("has taken a fork", philo);
	return (1);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_lock);
	philo->data->forks_tab[philo->l_fork] = 0;
	philo->data->forks_tab[philo->r_fork] = 0;
	pthread_mutex_unlock(&philo->data->forks_lock);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	write_lock("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	if (stop(philo->data))
		return (putdown_forks(philo), 0);
	putdown_forks(philo);
	if (stop(philo->data))
		return (0);
	return (1);
}
