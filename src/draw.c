/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:41 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 16:41:42 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	draw_wall_texture(t_cub *cub, t_ray ray, int *drawStart,
	int lineLength)
{
	t_texture	*texture;
	int			tex_x;
	float		step;
	float		texpos;
	int			pxl;

	texture = get_side_texture(ray.side, ray.dir.x, ray.dir.y, cub->textures);
	tex_x = (int)(ray.wallx * (float)texture->width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	step = 1.0 * texture->height / lineLength;
	texpos = (*drawStart - WIN_HEIGHT / 2 + lineLength / 2) * step;
	while (lineLength-- && WIN_HEIGHT > *drawStart)
	{
		pxl = texture->width * (int)texpos + tex_x;
		if (pxl >= 0)
			mlx_put_pixel(cub->render, ray.num, *drawStart,
				texture->pixels[pxl]);
		*drawStart = *drawStart + 1;
		texpos += step;
	}
	if (*drawStart < WIN_HEIGHT)
		mlx_put_pixel(cub->render, ray.num, *drawStart,
			cub->textures.f_color);
}

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

int	rgba_value(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
