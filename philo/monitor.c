/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:29:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 19:22:11 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->p_write_lock);
	printf("%010zu %d %s\n",
		get_ms_time() - philo->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(philo->p_write_lock);
}

bool	update_if_someone_die(t_philo *philo_arr)
{
	int		i;
	bool	is_someone_die;
	size_t	diff_time;

	i = 0;
	is_someone_die = false;
	while (i < philo_arr[0].num_of_philo)
	{
		pthread_mutex_lock(&(philo_arr[i].status_lock));
		diff_time = get_ms_time() - philo_arr[i].last_meal_time;
		if (diff_time >= (size_t)philo_arr[i].time_to_die)
		{
			philo_arr[i].status = DEAD;
			is_someone_die = true;
			print_message(&(philo_arr[i]), "died");
		}
		pthread_mutex_unlock(&(philo_arr[i].status_lock));
		i++;
	}
	return (is_someone_die);
}

bool	check_if_everyone_eat(t_philo *philo_arr)
{
	int	i;
	int	count;

	if (philo_arr[0].num_time_must_eat == -1)
		return (false);
	i = 0;
	count = 0;
	while (i < philo_arr[0].num_of_philo)
	{
		pthread_mutex_lock(&(philo_arr[i].status_lock));
		if (philo_arr[i].eat_cnt >= philo_arr[0].num_time_must_eat)
			count++;
		pthread_mutex_unlock(&(philo_arr[i].status_lock));
		i++;
	}
	return (count == philo_arr[0].num_of_philo);
}

void	*monitor(void *pointer)
{
	t_program	*program;
	
	program = (t_program *)pointer;
	while (true)
	{
		if (update_if_someone_die(program->philo) || \
			check_if_everyone_eat(program->philo))
			exit_simulation(program);
		ft_usleep(1);
	}
	return (NULL);
}
