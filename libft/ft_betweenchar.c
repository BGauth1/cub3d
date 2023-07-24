/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_betweenchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:44:53 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/10 19:00:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_betweenchar(const char *s, int n, char c)
{
	int		i;
	int		quote;

	if ((int)ft_strlen(s) <= n || n < 3)
		return (0);
	i = -1;
	quote = 0;
	while (++i != n)
	{
		if (s[i] == c)
			quote = !quote;
	}
	return (quote * (s[i] != c));
}
