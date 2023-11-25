/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:33:57 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/25 18:49:45 by lyeh             ###   ########.fr       */
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
	ft_usleep(philo->data->time_to_sleep);
}

void	do_eat(t_philo *philo)
{
	if (!grab_fork(philo))
		return ;
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal_time = get_ms_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&(philo->meal_lock));
	print_message(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	release_fork(philo);
}
