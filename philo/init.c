/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:41:14 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 19:21:14 by lyeh             ###   ########.fr       */
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

	program->philo = malloc(sizeof(t_philo) * program->num_of_philo);
	if (!program->philo)
		return (false);
	i = -1;
	while (++i < program->num_of_philo)
	{
		program->philo[i].id = i;
		program->philo[i].eat_cnt = 0;
		program->philo[i].num_of_philo = program->num_of_philo;
		program->philo[i].time_to_die = program->time_to_die;
		program->philo[i].time_to_eat = program->time_to_eat;
		program->philo[i].time_to_sleep = program->time_to_sleep;
		program->philo[i].num_time_must_eat = program->num_time_must_eat;
		program->philo[i].start_time = program->start_time;
		program->philo[i].last_meal_time = get_ms_time();
		program->philo[i].status = UNINITED;
		if (pthread_mutex_init(&(program->philo[i].status_lock), NULL) != 0)
			return (destory_philo_lock(program, i),
				free(program->philo), false);
		assign_fork(program, i);
		program->philo[i].p_write_lock = &(program->write);
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
	program->start_time = get_ms_time();
	if (argv[5] && ft_atoi(argv[5]) > 0)
		program->num_time_must_eat = ft_atoi(argv[5]);
	if (!init_program_lock(program))
		return (false);
	if (!init_philos(program))	
		return (destory_program_lock(program), false);
	return (true);
}
