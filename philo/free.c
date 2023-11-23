/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:58:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 00:05:12 by lyeh             ###   ########.fr       */
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

void	destory_philo_lock(t_program *program, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
		pthread_mutex_destroy(&(program->philo[i++].status_lock));
}

void	destory_program_lock(t_program *program)
{
	free_forks(program);
	pthread_mutex_destroy(&(program->write));
	pthread_mutex_destroy(&(program->lock));
}

void	free_all(t_program *program)
{
	free_forks(program);
	destory_program_lock(program);
	destory_philo_lock(program, program->num_of_philo);
	free(program->philo);
}

void    error_handle(t_program *program, char *msg)
{
	printf("Error: %s\n", msg);
	free_all(program);
	exit(UNEXCEPT_FAILED);
}
