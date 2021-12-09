/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:51:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/25 13:30:47 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write (1, str, i);
}

void	free_params(t_params *params)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&params->stop);
	pthread_mutex_destroy(&params->speak);
	while (i < params->nbr_philo)
	{
		pthread_mutex_destroy(&params->m_forks[i]);
		i++;
	}
	free(params->m_forks);
	free(params->philos);
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
