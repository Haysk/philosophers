/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:24:33 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/17 17:38:56 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

long int	time_to_ms(time_t sec, suseconds_t usec)
{
	long int	result;

	result = sec * 1000000 + usec;
	result /= 1000;
	return (result);
}

long int	get_time()
{
	long int	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = time_to_ms(tv.tv_sec, tv.tv_usec);
	return (time);
}

long int	get_timestamp(t_params *params)
{
	return (get_time() - params->time);
}
