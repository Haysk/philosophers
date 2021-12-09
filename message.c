/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:11:45 by adylewsk          #+#    #+#             */
/*   Updated: 2021/12/09 18:14:33 by adylewsk         ###   ########.fr       */
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
