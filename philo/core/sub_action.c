/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:06:55 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/26 22:24:24 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_everyone_alive(t_philo *philo)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&(philo->data->share_data_lock));
	if (philo->data->is_someone_die)
		ret = false;
	pthread_mutex_unlock(&(philo->data->share_data_lock));
	return (ret);
}

bool	grab_fork(t_philo *philo)
{
	if (!is_everyone_alive(philo))
		return (false);
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "taken r fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "taken l fork");
	return (true);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
