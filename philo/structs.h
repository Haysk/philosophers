/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:37:19 by adylewsk          #+#    #+#             */
/*   Updated: 2021/11/17 12:22:59 by adylewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

struct	s_params;

typedef struct	s_philo
{
	pthread_t	thread;
	int	id;
	int	fork_right;
	int	fork_left;
	int	remaining_eat;
	int	is_dead;
	struct s_params	*params;
}				t_philo;

typedef struct s_params
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_eat;
	int	eat_finished;
	t_philo			*philos;
	pthread_t	*nurses;	
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	speak;
	pthread_mutex_t	dead;
}				t_params;



#endif
