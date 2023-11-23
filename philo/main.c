#include "philo.h"

void	*loop_philo(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (philo->status != DEAD)
	{
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
	while (i < program->num_of_philo)
	{
		if (pthread_create(&(program->philo[i].thread), NULL,
				&loop_philo, &(program->philo[i])) != 0)
			error_handle(program, "create philo thread failed");
		i++;
	}
	if (pthread_join(manager, NULL) != 0)
		error_handle(program, "join manager thread failed");
	i = 0;
	while (i < program->num_of_philo)
	{
		if (pthread_join(program->philo[i].thread, NULL) != 0)
			error_handle(program, "join philo thread failed");
		i++;
	}
	return ;
}

int main(int argc, char **argv)
{
	t_program	program;

	if (!check_args_count(argc) || !check_input_content(argc, argv))
		return (UNEXCEPT_FAILED);
	if (!init_program(&program, argv))
		return (UNEXCEPT_FAILED);
	simulate(&program);
}
