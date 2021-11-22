/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/22 19:06:17 by adylewsk         ###   ########.fr       */
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
		if (ph_died(params, i))
			return (1);
		finished += params->philos[i].eat_finished;
		if (finished == params->nbr_philo)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	*routine_nurse(void *ptr_params)
{
	t_params	*params;

	params = (t_params *) ptr_params;
	printf("test a \n");
	pthread_mutex_lock(&params->stop);
	printf("test b \n");
	while (!check_philos(params))
	{
		usleep(200);
	}
	pthread_mutex_unlock(&params->stop);
	return (0);
}
void	*routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	philo->last_eat = get_time();
	if (philo->id % 2)
		usleep(60);
	while (philo->remaining_eat != 0)
	{
		take_fork(philo);
		ph_eat(philo);
		leave_fork(philo);
		put_message("is thinking", philo, get_timestamp(philo->params), 0);
	}
	philo->eat_finished = 1;
	return (0);
}

int	create_threads(t_params *params)
{
	int	i;
	t_philo *philos;

	i = 0;
	philos = params->philos;
	params->time = get_time();
	while (i < params->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, philos + i) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&params->nurses, NULL, routine_nurse, params) != 0)
		return (1);
	return (0);
}

int	philosophers(t_params *params)
{
	if (create_threads(params))
	{
		free_params(params);
		return (EXIT_FAILURE);
	}
	usleep(1000);
	pthread_mutex_lock(&params->stop);
	pthread_mutex_unlock(&params->stop);
	free_params(params);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int			error;
	t_params	params;

	error = 0;
	if (argc < 5 || argc > 6)
	{
		printf("./philo number_of_philosophers time_to_die time_to_eat %s",
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (!check_params(argv + 1))
		return (my_error("params", "only unsigned int"));
	if (init_params(&params, argc - 1, argv + 1))
	{
		free_params(&params);
		return (my_error("params", "unsigned int MAX RANGE"));
	}
	return (philosophers(&params));
}
