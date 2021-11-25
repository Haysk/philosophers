/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:30:16 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/16 13:20:19 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int	my_error(char *str, char *message)
{
	printf("%s : %s\n", str, message);
	return (EXIT_FAILURE);
}
