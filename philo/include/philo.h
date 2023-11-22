/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:48:23 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/22 20:39:00 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				eat_cnt;
	int				status;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_program
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_time_must_eat;
	bool			is_someone_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	t_philo			*philo;
}	t_program;


char	*ft_strtok(char *str);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_atoi(const char *str);

bool	check_input_content(int argc, char **argv);
bool	check_args_count(int argc);

bool	init_program(t_program *program, char **argv);

void	free_forks(t_program *program);
void	destory_program_lock(t_program *program);

#endif