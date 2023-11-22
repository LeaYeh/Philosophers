/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:14:08 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/21 22:38:08 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_input_digital(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < (int)ft_strlen(argv[i]))
		{
			if (!(j == 0 && argv[i][j] == '-') && !ft_isdigit(argv[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
bool	is_input_valid(char **argv)
{
	if (ft_atoi(argv[1]) < 1)
		return (write(2, "Invalid number of philosephers.\n", 32), false);
	else if (ft_atoi(argv[2]) < 1)
		return (write(2, "Invalid time to die.\n", 21), false);
	else if (ft_atoi(argv[3]) < 1)
		return (write(2, "Invalid time to eat.\n", 21), false);
	else if (ft_atoi(argv[4]) < 1)
		return (write(2, "Invalid time to sleep.\n", 23), false);
	else if (argv[5])
	{
		if (ft_atoi(argv[5]) < 1)
			return (write(2, 
				"Invalid number of times each philosopher must eat.\n", 52),
				false);
	}
	return (true);
}

bool	check_input_content(int argc, char **argv)
{
	if (!is_input_digital(argc, argv) || !is_input_valid(argv))
		return (false);
	return (true);
}

bool	check_args_count(int argc)
{
	if (argc == 6 || argc == 5)
		return (true);
	return (write(2, "Invalid input arguments count.\n", 31), false);
}
