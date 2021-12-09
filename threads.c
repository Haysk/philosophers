/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:06:24 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/09 18:16:33 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	check_philos(t_params *params)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < params->nbr_philo)
	{
		if (params->philos[i].remaining_eat != 0
			&& ph_died(&params->philos[i], params))
		{
			put_message("died", &params->philos[i], 1);
			return (1);
		}
		finished += params->philos[i].remaining_eat;
		i++;
	}
	if (finished == 0)
		return (1);
	return (0);
}

void	*routine_nurse(void *ptr_params)
{
	t_params	*params;

	params = (t_params *) ptr_params;
	while (check_philos(params) == 0)
		;
	params->quit = 1;
	pthread_mutex_unlock(&params->stop);
	return (0);
}

void	*routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	philo->last_eat = philo->params->time;
	if (philo->id % 2)
		usleep(100);
	while (philo->params->quit == 0 && philo->remaining_eat != 0)
	{
		take_fork(philo);
		ph_eat(philo);
		leave_fork(philo);
		if (philo->params->quit == 0 && philo->remaining_eat != 0)
			ph_sleep(philo);
	}
	return (0);
}

int	create_threads(t_params *params)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = params->philos;
	params->time = get_time();
	while (i < params->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	usleep(100);
	if (pthread_create(&params->nurses, NULL, routine_nurse, params) != 0)
		return (1);
	return (0);
}
