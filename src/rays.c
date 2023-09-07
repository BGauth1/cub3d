/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:04:23 by gbertet           #+#    #+#             */
/*   Updated: 2023/08/02 19:22:02 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_ray	init_ray(t_cub *cub, int iter)
{
	t_ray	ray;
    float   camera;

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
		ray->sideDist.x = (cub->player.coord.x - (float)cub->player.pos.x) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = ((float)cub->player.pos.x + 1.0 - cub->player.coord.x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (cub->player.coord.y - (float)cub->player.pos.y) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = ((float)cub->player.pos.y + 1.0 - cub->player.coord.y) * ray->deltaDist.y;
	}
}

t_ray	*get_rays(t_cub *cub)
{
    int     i;
    t_ray   *rays;

	rays = malloc((WIN_WIDTH) * sizeof(t_ray));
    i = -1;
    while (++i < WIN_WIDTH)
    {
        rays[i] = init_ray(cub, i);
		get_side_dist(cub, &rays[i]);
		while (rays[i].hit == 0)
		{
			if (rays[i].sideDist.x < rays[i].sideDist.y)
			{
				rays[i].sideDist.x += rays[i].deltaDist.x;
				cub->player.pos.x += rays[i].step.x;
				rays[i].side = 0;
			}
			else
			{
				rays[i].sideDist.y += rays[i].deltaDist.y;
				cub->player.pos.y += rays[i].step.y;
				rays[i].side = 1;
			}
			if (cub->map[cub->player.pos.y][cub->player.pos.x] == '1')
				rays[i].hit = 1;
		}
		// if (rays[i].side == 0)
			rays[i].perpWallDist = (rays[i].side == 0) ? (rays[i].sideDist.x - rays[i].deltaDist.x) : (rays[i].perpWallDist = rays[i].sideDist.y - rays[i].deltaDist.y);
		// 	rays[i].sideDist.x - rays[i].deltaDist.x;
		// else
		// 	rays[i].perpWallDist = rays[i].sideDist.y - rays[i].deltaDist.y;
    }
	return (rays);
}

void	draw_single_ray(t_cub *cub, t_ray ray, int color, int col)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int drawCeil;

	lineHeight = (int)(WIN_HEIGHT / ray.perpWallDist);
    drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
    if (drawStart < 0)drawStart = 0;
    drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
    if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	drawCeil = 0;
	while (drawCeil < drawStart)
		mlx_put_pixel(cub->render, col, drawCeil++, cub->textures.ceiling_color);
	while (drawStart <= drawEnd)
		mlx_put_pixel(cub->render, col, drawStart++, color);
	while (++drawEnd < WIN_HEIGHT)
		mlx_put_pixel(cub->render, col, drawEnd, cub->textures.floor_color);
}

void	draw_rays(t_cub *cub)
{
	t_ray	*rays;
	int	i;
	int	color;

	rays = get_rays(cub);
	i = -1;
	if (cub->key.m)
	{
		while (++i < WIN_WIDTH)
		{
			color = get_ray_color(rays[i]);
			draw_line(cub->render, fill_coord(cub->player.coord.x * 40, cub->player.coord.y * 40), fill_coord(cub->player.coord.x * 40.0 + rays[i].dir.x * rays[i].perpWallDist * 40.0, cub->player.coord.y * 40.0 + rays[i].dir.y * rays[i].perpWallDist * 40.0), color);
		}
	}
	else
	{
		while (++i < WIN_WIDTH)
		{
			color = get_ray_color(rays[i]);
			draw_single_ray(cub, rays[i], color, WIN_WIDTH - i - 1);
		}
	}
	free(rays);
}