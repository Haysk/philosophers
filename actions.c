/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:06:22 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/24 19:03:23 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	put_message(char *message, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->params->speak);
	printf("%li %i %s\n", get_timestamp(philo->params), philo->id, message);
	if (i == 0)
		pthread_mutex_unlock(&philo->params->speak);
	return (0);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->m_forks[philo->fork_left]);
	pthread_mutex_lock(&philo->params->m_forks[philo->fork_right]);
	put_message("has taken a fork", philo, 0);
	put_message("has taken a fork", philo, 0);
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
	put_message("is sleeping", philo, 0);
	while (get_time() - time < philo->params->time_to_sleep
		&& !philo->params->quit)
		usleep(200);
	put_message("is thinking", philo, 0);
	return (1);
}

int	ph_eat(t_philo *philo)
{
	philo->last_eat = get_time();
	put_message("is eating", philo, 0);
	if (philo->remaining_eat > 0)
		philo->remaining_eat--;
	while (get_time() - philo->last_eat < philo->params->time_to_eat
		&& !philo->params->quit)
		usleep(250);
	return (1);
}

int	ph_died(t_philo *philos, t_params *params)
{
	if (get_time() - philos->last_eat > params->time_to_die)
		return (1);
	return (0);
}
