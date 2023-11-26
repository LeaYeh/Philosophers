/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:33:57 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/26 22:03:47 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_think(t_philo *philo)
{
	print_message(philo, THINK_TEXT);
}

void	do_sleep(t_philo *philo)
{
	print_message(philo, SLEEP_TEXT);
	sleep_ms(philo->data->time_to_sleep);
}

void	do_eat(t_philo *philo)
{
	if (!grab_fork(philo))
		return ;
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal_time = get_ms_time();
	philo->eat_cnt++;
	pthread_mutex_unlock(&(philo->meal_lock));
	print_message(philo, EAT_TEXT);
	sleep_ms(philo->data->time_to_eat);
	release_fork(philo);
}
