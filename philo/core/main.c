/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:30:29 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/24 22:10:26 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(TIME_INTERVAL_UNIT);
	while (true)
	{
		pthread_mutex_lock(&(philo->dead_lock));
		if (philo->is_dead)
			break ;
		pthread_mutex_unlock(&(philo->dead_lock));
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
	}
	return (NULL);
}

void	simulate(t_program *program)
{
	pthread_t	manager;
	int			i;

	if (pthread_create(&manager, NULL, &monitor, program) != 0)
		error_handle(program, "create manager thread failed");
	i = 0;
	while (i < program->data.num_of_philo)
	{
		if (pthread_create(&(program->philo[i].thread), NULL,
				&loop_philo, &(program->philo[i])) != 0)
			error_handle(program, "create philo thread failed");
		i++;
	}
	if (pthread_join(manager, NULL) != 0)
		error_handle(program, "join manager thread failed");
	i = 0;
	while (i < program->data.num_of_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			error_handle(program, "join philo thread failed");
		printf("pthread_join %d\n", i);
		i++;
	}
	free_all(program);
	return ;
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (!check_args_count(argc) || !check_input_content(argc, argv))
		return (UNEXCEPT_FAILED);
	if (!init_program(&program, argv))
		return (UNEXCEPT_FAILED);
	// free_all(&program);
	simulate(&program);
}
