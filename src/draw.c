/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:41 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/28 19:44:32 by gbertet          ###   ########.fr       */
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

	int			tmp;

	texture = get_side_texture(ray.side, ray.dir.x, ray.dir.y, cub->textures);
	tex_x = (int)(ray.wallx * (float)texture->width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	step = 1.0 * texture->height / lineLength;
	texpos = (*drawStart - WIN_HEIGHT / 2 + lineLength / 2) * step;
	while (lineLength-- && WIN_HEIGHT > *drawStart)
	{
		tex_y = (int)texpos;
		texpos += step;
		tmp = texture->width * tex_y + tex_x;
		if (tmp >= 0)
		mlx_put_pixel(cub->render, ray.num, *drawStart,
			texture->pixels[tmp]);
		*drawStart = *drawStart + 1;
	}
	if (*drawStart < WIN_HEIGHT)
		mlx_put_pixel(cub->render, ray.num, *drawStart,
			cub->textures.f_color);
}

void	draw_texture(t_cub *cub, t_texture texture, t_pos pos)
{
	int	x;
	int	y;
	int	limit_x;
	int	limit_y;

	y = -1;
	limit_x = WIN_WIDTH - pos.x;
	limit_y = WIN_HEIGHT - pos.y;
	while (++y < texture.height && y < limit_y)
	{
		x = -1;
		while (++x < texture.width && x < limit_x)
			mlx_put_pixel(cub->render, x + pos.x, y + pos.y,
				texture.pixels[x + y * texture.width]);
	}
}
