/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:33:57 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 21:54:18 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_think(t_philo *philo)
{
	if (!is_alive(philo))
		return ;
	print_message(philo, "is thinking");
}

void	do_sleep(t_philo *philo)
{
	if (!is_alive(philo))
		return ;
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep);
}

void	do_eat(t_philo *philo)
{
	if (!is_alive(philo))
		return ;
	pthread_mutex_lock(&(philo->meal_lock));
	while (!grab_fork(philo))
		usleep(TIME_INTERVAL_UNIT);
	philo->last_meal_time = get_ms_time();
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat);
	release_fork(philo);
	pthread_mutex_unlock(&(philo->meal_lock));
}
