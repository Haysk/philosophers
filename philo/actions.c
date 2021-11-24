/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:06:22 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/23 16:04:45 by adylewsk         ###   ########.fr       */
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

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->m_forks[philo->fork_left]);
	put_message("has take a fork", philo, get_timestamp(philo->params), 0);
	pthread_mutex_lock(&philo->params->m_forks[philo->fork_right]);
	put_message("has take a fork", philo, get_timestamp(philo->params), 0);
}

void	leave_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->params->m_forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->params->m_forks[philo->fork_right]);
}

int	ph_sleep(t_philo *philo)
{
	long int	time;
	time = get_time();
	put_message("is sleeping", philo, get_timestamp(philo->params), 0);
	while (get_time() - time < philo->params->time_to_sleep)
		usleep(200);
	return (1);
}

int	ph_eat(t_philo *philo)
{
	philo->last_eat = get_time();
	put_message("is eating", philo, get_timestamp(philo->params), 0);
	while (get_time() - philo->last_eat < philo->params->time_to_eat)
		usleep(200);
	philo->remaining_eat--;
	return (1);
}

int	ph_died(t_params *params, int i)
{
	if (get_time() - params->philos[i].last_eat > params->time_to_die)
		return (1);
	return (0);
}
