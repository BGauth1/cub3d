/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:48:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 19:20:09 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_ray	init_ray(t_cub *cub, int iter)
{
	t_ray	ray;
	float	camera;

	camera = 2 * iter / (float)WIN_WIDTH - 1;
	ray.dir.x = cub->player.dir.x + cub->player.plane.x * camera;
	ray.dir.y = cub->player.dir.y + cub->player.plane.y * camera;
	cub->player.pos.x = (int)cub->player.coord.x;
	cub->player.pos.y = (int)cub->player.coord.y;
	if (ray.dir.x == 0)
		ray.deltaDist.x = 1e30;
	else
		ray.deltaDist.x = ft_fabs(1 / ray.dir.x);
	if (ray.dir.y == 0)
		ray.deltaDist.y = 1e30;
	else
		ray.deltaDist.y = ft_fabs(1 / ray.dir.y);
	ray.hit = 0;
	return (ray);
}

void	get_side_dist(t_cub *cub, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (cub->player.coord.x - (float)cub->player.pos.x)
			* ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = ((float)cub->player.pos.x + 1.0
				- cub->player.coord.x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (cub->player.coord.y - (float)cub->player.pos.y)
			* ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = ((float)cub->player.pos.y + 1.0
				- cub->player.coord.y) * ray->deltaDist.y;
	}
}

void	dda_loop(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			cub->player.pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			cub->player.pos.y += ray->step.y;
			ray->side = 1;
		}
		if (cub->map[cub->player.pos.y][cub->player.pos.x] == '1')
			ray->hit = 1;
	}
}

void	get_wall_data(t_cub *cub, t_ray *ray)
{
	if (!ray->side)
	{
		ray->perpWallDist = ray->sideDist.x - ray->deltaDist.x;
		ray->wallX = cub->player.coord.y + ray->perpWallDist * ray->dir.y;
	}
	else
	{
		ray->perpWallDist = ray->sideDist.y - ray->deltaDist.y;
		ray->wallX = cub->player.coord.x + ray->perpWallDist * ray->dir.x;
	}
	ray->wallX -= floor(ray->wallX);
	ray->wallX = 1 - ray->wallX;
}

void	get_rays(t_cub *cub, t_ray *rays)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		rays[i] = init_ray(cub, i);
		get_side_dist(cub, &rays[i]);
		dda_loop(cub, &rays[i]);
		get_wall_data(cub, &rays[i]);
	}
}
