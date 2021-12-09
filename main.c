/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/09 18:09:49 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

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
