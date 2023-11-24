/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:01:02 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 22:28:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_fork(t_program *program, int id)
{
	int	num_philo;

	num_philo = program->data.num_of_philo;
	program->philo[id].r_fork = &(program->forks[id]);
	if (num_philo == 1)
		program->philo[id].l_fork = NULL;
	else if (id == 0)
		program->philo[id].l_fork = &(program->forks[num_philo - 1]);
	else
		program->philo[id].l_fork = &(program->forks[id - 1]);
}

bool	init_philo_lock(t_program *program, t_philo *philo)
{
	philo->p_write_lock = &(program->write);
	if (pthread_mutex_init(&(philo->dead_lock), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(philo->meal_lock), NULL) != 0)
		return (pthread_mutex_destroy(&(philo->dead_lock)), false);
	return (true);
}

bool	init_philos(t_program *program)
{
	int	i;

	program->philo = malloc(sizeof(t_philo) * program->data.num_of_philo);
	if (!program->philo)
		return (false);
	i = 0;
	while (i < program->data.num_of_philo)
	{
		if (!init_philo_lock(program, program->philo))
			return (
				free_forks(program), destory_philo_lock(program, i), false);
		program->philo[i].id = i;
		program->philo[i].eat_cnt = 0;
		program->philo[i].data = &(program->data);
		program->philo[i].last_meal_time = get_ms_time();
		program->philo[i].is_dead = false;
		assign_fork(program, i);
		i++;
	}
	return (true);
}

void	destory_philo_lock(t_program *program, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&(program->philo[i].meal_lock));
		pthread_mutex_destroy(&(program->philo[i].dead_lock));
		i++;
	}
}
