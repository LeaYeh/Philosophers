#include "philo.h"

int main(int argc, char **argv)
{
	t_program	program;

	if (!check_args_count(argc) || !check_input_content(argc, argv))
		return (-1);
	init_program(&program, argv);
}
