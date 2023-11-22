/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:41:14 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/22 21:13:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_forks(t_program *program)
{
	int	i;

	program->forks = (pthread_mutex_t *)malloc(
		sizeof(pthread_mutex_t) * program->num_of_philo);
	if (!program->forks)
		return (false);
	i = 0;
	while (i < program->num_of_philo)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL) != 0)
			return (free(program->forks), false);
		i++;
	}
	return (true);
}

void	assign_fork(t_program *program, int id)
{
	int	num_philo;

	num_philo = program->num_of_philo;
	program->philo[id].r_fork = &(program->forks[id]);
	if (program->num_of_philo == 1)
		program->philo[id].l_fork = NULL;
	else if (id == 0)
		program->philo[id].l_fork = &(program->forks[num_philo - 1]);
	else
		program->philo[id].l_fork = &(program->forks[id - 1]);
}

bool	init_philos(t_program *program)
{
	int	i;
	int	num_philo;

	num_philo = program->num_of_philo;
	program->philo = (t_philo *)malloc(sizeof(t_philo) * num_philo);
	if (!program->philo)
		return (false);
	i = 0;
	while (i < num_philo)
	{
		program->philo[i].id = i;
		program->philo[i].eat_cnt = 0;
		program->philo[i].status = 0;
		assign_fork(program, i);
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
	program->is_someone_die = false;
	program->num_of_philo = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	program->num_time_must_eat = -1;
	if (argv[5] && ft_atoi(argv[5]) > 0)
		program->num_time_must_eat = ft_atoi(argv[5]);
	if (!init_program_lock(program))
		return (false);
	if (!init_philos(program))	
		return (destory_program_lock(program), false);
	return (true);
}
