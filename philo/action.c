/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:33:57 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 19:13:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_think(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&(philo->status_lock));
	philo->status = THINK;
	print_message(philo, "is thinking");
	pthread_mutex_unlock(&(philo->status_lock));
}

void	do_sleep(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&(philo->status_lock));
	philo->status = SLEEP;
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_unlock(&(philo->status_lock));
}

bool	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	if (philo->num_of_philo == 1)
	{
		ft_usleep(philo->time_to_die);
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

void	do_eat(t_philo *philo)
{
	if (philo->status == DEAD)
		return ;
	pthread_mutex_lock(&(philo->status_lock));
	if (grab_fork(philo))
	{
		philo->status = EAT;
		philo->last_meal_time = get_ms_time();
		print_message(philo, "is eating");
		ft_usleep(philo->time_to_eat);
		release_fork(philo);
	}
	pthread_mutex_unlock(&(philo->status_lock));
}
