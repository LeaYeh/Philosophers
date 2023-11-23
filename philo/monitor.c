/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:29:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/23 07:24:11 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->p_write_lock));
	printf("%ld %d %s\n", get_ms_time(), philo->id + 1, msg);
	pthread_mutex_unlock(&(philo->p_write_lock));
}
