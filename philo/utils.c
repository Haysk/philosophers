/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/17 14:21:52 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	free_params(t_params *params)
{
	int	i;

	i = 0;
	free(params->philos);
	free(params->nurses);
	while (i < params->nbr_philo)
	{
		pthread_mutex_destroy(&params->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->speak);
	pthread_mutex_destroy(&params->stop);
	free(params->m_forks);
}

int	my_usleep(unsigned int usec)
{
	unsigned int	time;

	time = 50;
	while (usec > 0)
	{
		if (usleep(time) == -1)
			return (-1);
		usec -= time;
	}
	return (0);
}

int	my_atopi(const char *str, int *error)
{
	unsigned long	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t'
	|| *str == '\v' || *str == '\f' || *str == '\r')
		str = str + 1;
	if (*str == '-')
	{
		*error = 1;
		return (0);
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		if (nbr > INT_MAX)
			*error = 1;
		str++;
	}
	return ((int)nbr);
}

int	is_unum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
