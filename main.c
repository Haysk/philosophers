/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/24 18:59:24 by adylewsk         ###   ########.fr       */
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

int	philosophers(t_params *params)
{
	pthread_mutex_lock(&params->stop);
	if (create_threads(params))
	{
		ft_putstr("error\n");
		free_params(params);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(&params->stop);
	pthread_mutex_unlock(&params->stop);
	usleep(2500 * params->nbr_philo);
	free_params(params);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_params	params;

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
