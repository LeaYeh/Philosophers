#include "philo.h"

void	loop_philo(t_philo *philo)
{
	while (philo->status != DEAD)
	{
		/* code */
	}
	
}

int main(int argc, char **argv)
{
	t_program	program;

	if (!check_args_count(argc) || !check_input_content(argc, argv))
		return (UNEXCEPT_FAILED);
	if (!init_program(&program, argv))
		return (UNEXCEPT_FAILED);
}
