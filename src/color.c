/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:41 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 19:20:02 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_line(mlx_image_t *data, t_coord begin, t_coord end, int color)
{
	float	diffx;
	float	diffy;
	float	max_diff;
	int		i;
	t_coord	incr;

	i = -1;
	if (begin.x > end.x)
	{
		ft_fswap(&begin.x, &end.x);
		ft_fswap(&begin.y, &end.y);
	}
	diffx = end.x - begin.x;
	diffy = end.y - begin.y;
	if (ft_abs(diffx) > ft_abs(diffy))
		max_diff = ft_abs(diffx);
	else
		max_diff = ft_abs(diffy);
	incr = fill_coord(diffx / max_diff, diffy / max_diff);
	while (++i < max_diff)
	{
		mlx_put_pixel(data, begin.x, begin.y, color);
		begin.x += incr.x;
		begin.y += incr.y;
	}
}

void	draw_rectangle(mlx_image_t *data, t_pos begin, t_pos end, int color)
{
	int	tmp;

	tmp = begin.x;
	while (begin.y <= end.y)
	{
		while (begin.x <= end.x)
			mlx_put_pixel(data, begin.x++, begin.y, color);
		begin.x = tmp;
		begin.y++;
	}
}

void	draw_wall_texture(t_cub *cub, t_ray ray, int *drawStart,
	int lineLength)
{
	t_texture	*texture;
	int			tex_x;
	int			tex_y;
	float		step;
	float		texpos;

	texture = get_side_texture(ray.side, ray.dir.x, ray.dir.y, cub->textures);
	tex_x = (int)(ray.wallX * (float)texture->width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	step = 1.0 * texture->height / lineLength;
	texpos = (*drawStart - WIN_HEIGHT / 2 + lineLength / 2) * step;
	while (lineLength-- && WIN_HEIGHT > *drawStart)
	{
		tex_y = (int)texpos;
		texpos += step;
		mlx_put_pixel(cub->render, ray.num, *drawStart,
			texture->pixels[texture->width * tex_y + tex_x]);
		*drawStart = *drawStart + 1;
	}
	if (*drawStart < WIN_HEIGHT)
		mlx_put_pixel(cub->render, ray.num, *drawStart,
			cub->textures.floor_color);
}

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
