/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:00:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 22:31:56 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_data_lock(t_data *data)
{
	if (pthread_mutex_init(&(data->share_data_lock), NULL) != 0)
		return (false);
	return (true);
}

bool	init_data(t_data *data, char **argv)
{
	if (!init_data_lock(data))
		return (false);
	data->is_someone_die = false;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_time_must_eat = -1;
	data->start_time = get_ms_time();
	if (argv[5] && ft_atoi(argv[5]) > 0)
		data->num_time_must_eat = ft_atoi(argv[5]);
	return (true);
}

void	destory_data_lock(t_data *data)
{
	pthread_mutex_destroy(&(data->share_data_lock));
}
