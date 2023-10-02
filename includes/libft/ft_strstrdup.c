/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:56:33 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/10 16:57:16 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strstrdup(const char **s)
{
	int		i;
	char	**res;

	i = 0;
	while (s[i])
		i++;
	res = malloc((i + 1) * sizeof (char *));
	i = 0;
	while (s[i])
	{
		res[i] = ft_strdup(s[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}
