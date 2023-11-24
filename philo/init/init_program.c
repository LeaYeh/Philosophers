/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:59:39 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 22:30:08 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destory_program_lock(t_program *program)
{
	pthread_mutex_destroy(&(program->write));
	pthread_mutex_destroy(&(program->lock));
}

bool	init_forks(t_program *program)
{
	int	i;

	program->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * program->data.num_of_philo);
	if (!program->forks)
		return (false);
	i = 0;
	while (i < program->data.num_of_philo)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL) != 0)
			return (free(program->forks), false);
		i++;
	}
	return (true);
}

bool	init_program_lock(t_program *program)
{
	if (!init_forks(program))
		return (false);
	if (pthread_mutex_init(&(program->write), NULL) != 0)
		return (free_forks(program), false);
	if (pthread_mutex_init(&(program->lock), NULL) != 0)
		return (free_forks(program),
			pthread_mutex_destroy(&(program->write)), false);
	return (true);
}

bool	init_program(t_program *program, char **argv)
{
	if (!init_data(&(program->data), argv))
		return (false);
	if (!init_program_lock(program))
		return (destory_data_lock(&(program->data)), false);
	if (!init_philos(program))
		return (destory_data_lock(&(program->data)),
			destory_program_lock(program), false);
	return (true);
}
