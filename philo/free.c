/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:58:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/22 21:06:10 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philo)
		pthread_mutex_destroy(&(program->forks[i++]));
	free(program->forks);
}

void	destory_program_lock(t_program *program)
{
	free_forks(program);
	pthread_mutex_destroy(&(program->write));
	pthread_mutex_destroy(&(program->lock));
}

void    error_handle(t_program *program, char *msg)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	free_forks(program);
	destory_program_lock(program);
	free(program->philo);
}
