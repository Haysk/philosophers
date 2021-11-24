/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/23 17:29:00 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	check_philos(t_params *params)
{
//	int	i;
//	int	finished;
//
//	i = 0;
//	finished = 0;
//	while (i < params->nbr_philo)
//	{
//
//		if (!params->philos[i].eat_finished && ph_died(params, i))
//		{
//			printf("dead\n");
//			put_message("die", &params->philos[i], get_timestamp(params), 1);
//			return (1);
//		}
//		finished += params->philos[i].eat_finished;
//		if (finished == params->nbr_philo)
//		{
//			return (1);
//		}
//		usleep(200);
//		i++;
//	}
	(void)params;
	return (0);
}

void	*routine_nurse(void *ptr_params)
{
	t_params	*params;

	params = (t_params *) ptr_params;
	while (!check_philos(params));
	params->quit = 1;
	pthread_mutex_unlock(&params->stop);
	ft_putstr("nurse\n");
	return (0);
}

void	*routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	philo->last_eat = get_time();
//	if (!(philo->id % 2))
//		usleep(200);
	while (!philo->params->quit)
	{
		take_fork(philo);
		ph_eat(philo);
		leave_fork(philo);
		ph_sleep(philo);
		put_message("is thinking", philo, get_timestamp(philo->params), 0);
	}
	philo->eat_finished = 1;
	ft_putstr("thread finished\n");
	return (0);
}

int	create_threads(t_params *params)
{
	int	i;
	t_philo *philos;
	pthread_t	thread;
	i = 0;
	philos = params->philos;
	params->time = get_time();
	if (pthread_create(&thread, NULL, routine_nurse, params) != 0)
		return (1);
	pthread_detach(thread);
	while (i < params->nbr_philo)
	{
		if (pthread_create(&thread, NULL, routine, philos + i) != 0)
			return (1);
		pthread_detach(thread);
		i++;
	}
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
	ft_putstr("main lock\n");
	pthread_mutex_unlock(&params->stop);
	free_params(params);
	sleep(1);
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
