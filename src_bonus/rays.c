/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:04:23 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/02 17:00:51 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_single_ray(t_cub *cub, t_ray ray, int col)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	drawceil;

	lineheight = (int)(WIN_HEIGHT / (ray.wall_dist * 1.2));
	drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + WIN_HEIGHT / 2;
	if (drawend >= WIN_HEIGHT)
		drawend = WIN_HEIGHT - 1;
	drawceil = 0;
	while (drawceil < drawstart)
		mlx_put_pixel(cub->render, col, drawceil++,
			cub->textures.c_color);
	draw_wall_texture(cub, ray, &drawstart, lineheight);
	while (++drawend < WIN_HEIGHT)
		mlx_put_pixel(cub->render, col, drawend,
			cub->textures.f_color);
}

void	draw_rays_map(t_cub *cub, int size)
{
	int	color;
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		color = get_ray_color(cub->player.rays[i]);
		draw_line(cub->render, fill_coord(cub->player.coord.x * size, cub
				->player.coord.y * size), fill_coord(cub->player.coord.x
				* size + cub->player.rays[i].dir.x * cub->player.rays[i]
				.wall_dist * size, cub->player.coord.y * size + cub
				->player.rays[i].dir.y * cub->player.rays[i].wall_dist
				* size), color);
	}
}

void	draw_rays(t_cub *cub)
{
	int	i;
	int	color;

	get_rays(cub, cub->player.rays);
	i = -1;
	if (cub->key.m)
	{
		if (cub->key.r)
			draw_rays_map(cub, cub->m_map.wall_size);
	}
	else
	{
		while (++i < WIN_WIDTH)
		{
			color = get_ray_color(cub->player.rays[i]);
			draw_single_ray(cub, cub->player.rays[i], WIN_WIDTH - i - 1);
		}
	}
}
