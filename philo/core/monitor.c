/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:29:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/25 18:38:30 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	if (!is_alive(philo))
		return ;
	pthread_mutex_lock(philo->p_write_lock);
	printf("%zu %d %s\n",
		get_ms_time() - philo->data->start_time, philo->id + 1, msg);
	pthread_mutex_unlock(philo->p_write_lock);
}

void	update_die_status(t_philo *philo_arr)
{
	size_t	diff_time;
	int		i;

	i = 0;
	while (i < philo_arr[0].data->num_of_philo)
	{
		pthread_mutex_lock(&(philo_arr[i].meal_lock));
		diff_time = get_ms_time() - philo_arr[i].last_meal_time;
		if (diff_time >= (size_t)philo_arr[i].data->time_to_die)
		{
			pthread_mutex_unlock(&(philo_arr[i].meal_lock));
			break ;
		}
		pthread_mutex_unlock(&(philo_arr[i].meal_lock));
		i++;
	}
	if (i < philo_arr[0].data->num_of_philo)
	{
		print_message(&(philo_arr[i]), "is die");
		pthread_mutex_lock(&(philo_arr[i].data->share_data_lock));
		philo_arr[i].data->is_someone_die = true;
		pthread_mutex_unlock(&(philo_arr[i].data->share_data_lock));
	}
}

bool	check_if_everyone_eat(t_philo *philo_arr)
{
	int	i;
	int	count;

	if (philo_arr[0].data->num_time_must_eat == -1)
		return (false);
	i = 0;
	count = 0;
	while (i < philo_arr[0].data->num_of_philo)
	{
		pthread_mutex_lock(&(philo_arr[i].meal_lock));
		if (philo_arr[i].eat_cnt >= philo_arr[0].data->num_time_must_eat)
			count++;
		pthread_mutex_unlock(&(philo_arr[i].meal_lock));
		i++;
	}
	return (count == philo_arr[0].data->num_of_philo);
}

bool	check_if_someone_die(t_program *program)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&(program->data.share_data_lock));
	if (program->data.is_someone_die)
		ret = true;
	pthread_mutex_unlock(&(program->data.share_data_lock));
	return (ret);
}

void	*monitor(void *pointer)
{
	t_program	*program;

	program = (t_program *)pointer;
	while (true)
	{
		update_die_status(program->philo);
		if (check_if_everyone_eat(program->philo))
		{
			pthread_mutex_lock(&(program->data.share_data_lock));
			program->data.is_someone_die = true;
			pthread_mutex_unlock(&(program->data.share_data_lock));
		}
		if (check_if_someone_die(program))
			break ;
		// usleep(TIME_INTERVAL_UNIT);
	}
	return (NULL);
}
