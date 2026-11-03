/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:37:07 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/10 09:54:35 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	print_error(char *s)
{
	printf("%s\n", s);
	return (1);
}

int	parser(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (printf("Try : ./philo 2 800 200 200/n"));
	if (!ft_isnum(av[1]) || ft_atoi(av[1]) > INT_MAX || ft_atoi(av[1]) == 0)
		return (printf("Error\n nb philo"), 1);
	data->nb_philo = ft_atoi(av[1]);
	if (!ft_isnum(av[2]) || ft_atoi(av[2]) > INT_MAX || ft_atoi(av[2]) == 0)
		return (printf("Error\n time to die"), 1);
	data->time_to_die = ft_atoi(av[2]);
	if (!ft_isnum(av[3]) || ft_atoi(av[3]) > INT_MAX || ft_atoi(av[3]) == 0)
		return (printf("Error\n time to eat"), 1);
	data->time_to_eat = ft_atoi(av[3]);
	if (!ft_isnum(av[4]) || ft_atoi(av[4]) > INT_MAX || ft_atoi(av[4]) == 0)
		return (printf("Error\n time to sleep"), 1);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		if (!ft_isnum(av[5]) || ft_atoi(av[5]) > INT_MAX || ft_atoi(av[5]) == 0)
			return (printf("Error\n nb philo"), 1);
		data->nb_meal = ft_atoi(av[5]);
	}
	else
		data->nb_meal = -1;
	return (0);
}
