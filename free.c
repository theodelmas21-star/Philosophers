/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:24:53 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:19 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_mutex(t_data *data, int res)
{
	if (res >= 2)
	{
		if (pthread_mutex_destroy(&data->dead_lock))
			perror("pthread mutex destroy failed");
		return ;
	}
	if (res >= 3)
	{
		if (pthread_mutex_destroy(&data->meal_lock))
			perror("pthread mutex destroy failed");
		return ;
	}
	if (res >= 4)
	{
		if (pthread_mutex_destroy(&data->write_lock))
			perror("pthread mutex destroy failed");
		return ;
	}
	if (res >= 5)
	{
		if (pthread_mutex_destroy(&data->forks_lock))
			perror("pthread mutex destroy failed");
		return ;
	}
}

void	free_all(t_data *data)
{
	free_mutex(data, 5);
	free(data->forks_tab);
	free(data->philos);
	free(data);
}
