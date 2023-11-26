/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:20:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/26 21:51:58 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_ms_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	sleep_ms(size_t ms)
{
	size_t	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < ms)
		usleep(500);
	return (0);
}
