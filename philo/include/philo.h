/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:48:23 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 07:40:33 by lyeh             ###   ########.fr       */
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
# include <sys/time.h>

# define UNEXCEPT_FAILED 42
# define TIME_INTERVAL_UNIT 500

typedef enum s_status_code
{
	UNINITED = -1,
	THINK,
	SLEEP,
	EAT,
	DEAD
}	t_status_code;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_cnt;
	size_t			last_meal_time;
	t_status_code	status;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	*p_write_lock;
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
void	destory_philo_lock(t_program *program, int num_philo);

size_t	get_ms_time(void);

#endif