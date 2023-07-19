/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:41 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/19 15:12:38 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_right(mlx_image_t *data, t_coord begin, t_coord end, int color)
{
	float	diffx;
	float	diffy;
	float	max_diff;
	int		i;
	t_coord	incr;

	i = -1;
	diffx = end.x - begin.x;
	diffy = end.y - begin.y;
	if (ft_abs(diffx) > ft_abs(diffy))
		max_diff = diffx;
	else
		max_diff = diffy;
	incr = fill_coord(diffx / max_diff, diffy / max_diff);
	while (++i < max_diff)
	{
		mlx_put_pixel(data, begin.x, begin.y, color);
		begin.x += incr.x;
		begin.y += incr.y;
	}
}

void	draw_line_left(mlx_image_t *data, t_pos begin, t_pos end, int color)
{
	int	a;
	int	b;
	int	p;

	// printf("x1 = %d, y1 = %d\nx2 = %d, y2 = %d\n", begin.x, begin.y, end.x, end.y);
	a = 2 * ft_abs(begin.y - end.y);
	b = 2 - 2 * ft_abs(begin.x - end.x);
	p = a - ft_abs(begin.x - end.x);
	// mlx_put_pixel(data, begin.x, begin.y, argb_value(0, 0, 0, 255));
	while (begin.x >= end.x)
	{
		mlx_put_pixel(data, begin.x, begin.y, color);
		if (p < 0)
		{
			begin.x--;
			p += a;
		}
		if (p >= 0)
		{
			if (begin.y < end.y)
				begin.y++;
			else
				begin.y--;
			p += b;
		}
	}
	// mlx_put_pixel(data, end.x, end.y, argb_value(0, 0, 0, 255));
}

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

int	argb_value(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
