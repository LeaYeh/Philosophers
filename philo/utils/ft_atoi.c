/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:55:49 by lyeh              #+#    #+#             */
/*   Updated: 2023/11/30 12:08:46 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	_safe_calc(long nb1, long nb2, int sign)
{
	if (sign > 0 && nb1 > (LONG_MAX - nb2) / 10)
		return (LONG_MAX);
	else if (sign < 0 && (nb1 + 1) > (LONG_MAX - nb2) / 10)
		return (LONG_MIN);
	return (nb1 * 10 + nb2);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] && ft_isdigit(str[i]) && nbr != LONG_MAX && nbr != LONG_MIN)
		nbr = _safe_calc(nbr, str[i++] - '0', sign);
	nbr *= sign;
	return ((int) nbr);
}
