/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:21:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 21:20:32 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atois(const char *nptr)
{
	int	neg;
	int	nb;

	nb = 0;
	neg = 1;
	while (*nptr == 32 || (*nptr >= 8 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb += *nptr - 48;
		nptr++;
	}
	return (nb * neg);
}

int	ft_atoi(const char *s, int *err)
{
	long long	result;
	int			neg;
	int			i;

	result = 0;
	neg = 1;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			neg = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - '0';
		if (result * neg > 2147483647 || result * neg < -2147483648)
			*err = -42;
		i++;
	}
	result *= neg;
	return ((int)result);
}
