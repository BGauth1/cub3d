/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:48:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 17:23:11 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static t_ray	init_ray(t_cub *cub, int iter)
{
	t_ray	ray;
	float	camera;

	camera = 2 * iter / (float)WIN_WIDTH - 1;
	ray.dir.x = cub->player.dir.x + cub->player.plane.x * camera;
	ray.dir.y = cub->player.dir.y + cub->player.plane.y * camera;
	cub->player.pos.x = (int)cub->player.coord.x;
	cub->player.pos.y = (int)cub->player.coord.y;
	if (ray.dir.x == 0)
		ray.delta_dist.x = 1e30;
	else
		ray.delta_dist.x = ft_fabs(1 / ray.dir.x);
	if (ray.dir.y == 0)
		ray.delta_dist.y = 1e30;
	else
		ray.delta_dist.y = ft_fabs(1 / ray.dir.y);
	ray.hit = 0;
	return (ray);
}

static void	get_side_dist(t_cub *cub, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (cub->player.coord.x - (float)cub->player.pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = ((float)cub->player.pos.x + 1.0
				- cub->player.coord.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (cub->player.coord.y - (float)cub->player.pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = ((float)cub->player.pos.y + 1.0
				- cub->player.coord.y) * ray->delta_dist.y;
	}
}

static void	dda_loop(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			cub->player.pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			cub->player.pos.y += ray->step.y;
			ray->side = 1;
		}
		if (cub->map[cub->player.pos.y][cub->player.pos.x] == '1')
			ray->hit = 1;
	}
}

static void	get_wall_data(t_cub *cub, t_ray *ray)
{
	if (!ray->side)
	{
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
		ray->wallx = cub->player.coord.y + ray->wall_dist * ray->dir.y;
	}
	else
	{
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
		ray->wallx = cub->player.coord.x + ray->wall_dist * ray->dir.x;
	}
	ray->wallx -= floor(ray->wallx);
	ray->wallx = 1 - ray->wallx;
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
		draw_single_ray(cub, cub->player.rays[i], WIN_WIDTH - i - 1);
	}
}
