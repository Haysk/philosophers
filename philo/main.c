/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/17 12:27:54 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "headers.h"

void	*routine_nurse(void *philo)
{
	t_philo	*ptr_philo;

	ptr_philo = (t_philo *)philo;
	while (!ptr_philo->is_dead && !ptr_philo->eat_finished);
	ptr_philo->params->eat_finished++;
	printf("dead\n");
	pthread_mutex_unlock(&ptr_philo->params->dead);
	return (0);
}
void	*routine(void *philo)
{
	t_philo	*ptr_philo;

	ptr_philo = (t_philo *)philo;
	while (ptr_philo->remaining_eat != 0)
	{
		sleep(2);
		printf("thread %i : %i\n",ptr_philo->id, ptr_philo->remaining_eat);
		if (ptr_philo->remaining_eat > 0)
			ptr_philo->remaining_eat--;
	}
	ptr_philo->eat_finished = 1;
	return (0);
}

int	create_threads(t_params *params)
{
	int	i;
	t_philo *philos;

	i = 0;
	philos = params->philos;
	while (i < params->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, philos + i) != 0 ||
			pthread_create(&params->nurses[i], NULL, routine_nurse, philos + i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	philosophers(t_params *params)
{
	if (create_threads(params))
	{
		free_params(params);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&params->dead);
	pthread_mutex_unlock(&params->dead);
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
