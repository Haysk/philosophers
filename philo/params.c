/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:29:28 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/17 12:23:45 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"


void	init_mutex(t_params *params)
{
	int	i;

	i = 0;
	pthread_mutex_init(&params->speak, NULL);
	pthread_mutex_init(&params->dead, NULL);
	pthread_mutex_lock(&params->dead);
	while (i < params->nbr_philo)
	{
		pthread_mutex_init(&params->m_forks[i], NULL);
		i++;
	}
}

void	init_philos(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nbr_philo)
	{
		params->philos[i].id = i + 1;
		params->philos[i].is_dead = 0;
		params->philos[i].fork_left = i + 1;
		params->philos[i].fork_right = i;
		if (i == 0)
			params->philos[i].fork_right = params->nbr_philo;
		params->philos[i].remaining_eat = params->nbr_eat;
		params->philos[i].params = params;
		i++;
	}
}

int	init_params(t_params *params, int argc, char **argv)
{
	int	error;

	error = 0;
	params->nbr_philo = my_atopi(argv[0], &error);
	params->time_to_die = my_atopi(argv[1], &error);
	params->time_to_eat = my_atopi(argv[2], &error);
	params->time_to_sleep = my_atopi(argv[3], &error);
	params->nbr_eat = -1;
	params->eat_finihed = 0;
	if (argc == 5)
		params->nbr_eat = my_atopi(argv[4], &error);
	params->philos = malloc(sizeof(t_philo) * params->nbr_philo);
	params->m_forks = malloc(sizeof(pthread_mutex_t) * params->nbr_philo);
	params->nurses = malloc(sizeof(pthread_t) * params->nbr_philo);
	if (params->philos == NULL || params->m_forks == NULL
		|| params->nurses == NULL)
	{
		free(params->philos);
		return (1);
	}
	init_philos(params);
	init_mutex(params);
	return (error);
}
