/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:32:02 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 16:46:53 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_pos	fill_pos(int x, int y)
{
	t_pos	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_coord	fill_coord(float x, float y)
{
	t_coord	res;

	res.x = x;
	res.y = y;
	return (res);
}

int	ft_abs(int i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}

float	ft_fabs(float x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}
