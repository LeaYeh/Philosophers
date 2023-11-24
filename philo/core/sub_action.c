/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:06:55 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 22:11:03 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(t_philo *philo)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&(philo->dead_lock));
	if (philo->is_dead)
		ret = false;
	pthread_mutex_lock(&(philo->dead_lock));
	return (ret);
}

bool	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->num_of_philo == 1)
	{
		usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	return (true);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
