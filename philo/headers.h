/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:53:22 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/23 15:26:05 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include "structs.h"

void	free_params(t_params *params);
int		my_error(char *str, char *message);
long int	get_time();
long int	get_timestamp(t_params *params);
int		my_usleep(unsigned int sec);
int		is_unum(char *str);
int		my_atopi(const char *str, int *error);
int		check_params(char	**args);
int		init_params(t_params *params, int argc, char **argv);
int		put_message(char *message, t_philo *philo, long int time, int lock);
void	take_fork(t_philo *philo);
int		ph_eat(t_philo *philo);
int		ph_sleep(t_philo *philo);
void	leave_fork(t_philo *philo);
int		ph_died(t_params *params, int i);
#endif
