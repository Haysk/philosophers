/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:06:22 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/22 13:38:04 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	put_message(char *message, t_philo *philo, long int time, int lock)
{
	pthread_mutex_lock(&philo->params->speak);
	printf("%li %i %s\n", time, philo->id, message);
	if (!lock)
		pthread_mutex_unlock(&philo->params->speak);
	return (0);
}

int	use_fork(t_philo *philo, int id, int is_take)
{
	if (is_take)
	{
		pthread_mutex_lock(&philo->params->m_forks[id - 1]);	
		put_message("has take a fork", philo, get_timestamp(philo->params), 0);
	}
	else
		pthread_mutex_unlock(&philo->params->m_forks[id - 1]);	
	return (0);
}

int	ph_eat(t_philo *philo)
{
	long int	time;

	use_fork(philo, philo->fork_left, 1);
	use_fork(philo, philo->fork_right, 1);
	time = get_timestamp(philo->params);
	put_message("is eating", philo, time, 0);
	while (get_timestamp(philo->params) - time < philo->params->time_to_eat)
		usleep(200);
	philo->last_eat = time + philo->params->time_to_eat;
	philo->remaining_eat--;
	use_fork(philo, philo->fork_right, 0);
	use_fork(philo, philo->fork_left, 0);
	return (1);
}

int	ph_sleep(t_philo *philo)
{
	long int	time;

	time = get_timestamp(philo->params);
	put_message("is sleeping", philo, time, 0);
	while (get_timestamp(philo->params) - time < philo->params->time_to_sleep)
		usleep(200);
	put_message("is thinking", philo, get_timestamp(philo->params), 0);
	return (1);
}

int	ph_died(t_philo *philo)
{
	if (get_timestamp(philo->params) - philo->last_eat
		> philo->params->time_to_die)
	{
			printf("last eat : %i, time : %li, dead : %i\n", philo->last_eat, get_timestamp(philo->params), philo->params->time_to_die);
		put_message("die", philo, get_timestamp(philo->params), 1);
		return (1);
	}
	return (0);
}
