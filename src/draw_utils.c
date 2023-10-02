/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:02:12 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/29 17:04:27 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_ray_color(t_ray ray)
{
	if (ray.side == 1 && ray.dir.y > 0)
		return (rgba_value(255, 0, 0, 255));
	else if (ray.side == 0 && ray.dir.x > 0)
		return (rgba_value(0, 255, 255, 255));
	else if (ray.side == 1)
		return (rgba_value(0, 0, 255, 255));
	return (rgba_value(0, 255, 0, 255));
}

int	rgba_value(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
