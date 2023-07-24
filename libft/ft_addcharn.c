/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addcharn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:57 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/10 18:37:47 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_addcharn(char *s, char c, int n)
{
	int	i;

	i = ft_strlen(s);
	if (!i)
		return (s);
	s = ft_realloc(s, i, i + 1);
	if (!s)
		return (s);
	s[i + 1] = '\0';
	while (i != n)
	{
		s[i] = s[i - 1];
		i--;
	}
	s[n] = c;
	return (s);
}
