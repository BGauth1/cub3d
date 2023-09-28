/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:19:07 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/28 18:30:43 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	render_map(mlx_image_t *img, char **map)
{
	int		i;
	int		j;
	int		color;

	i = -1;
	(void)map;
	draw_rectangle(img, fill_pos(0, 0),
		fill_pos(WIN_WIDTH - 1, WIN_HEIGHT - 1), rgba_value(0, 0, 0, 255));
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				color = rgba_value(255, 0, 0, 255);
			else
				color = rgba_value(0, 0, 0, 255);
			draw_rectangle(img, fill_pos(j * 10, i * 10),
				fill_pos((j + 1) * 10 - 1, (i + 1) * 10 - 1), color);
		}
	}
}

void	render_player(mlx_image_t *img, t_player player)
{
	draw_rectangle(img, fill_pos(player.coord.x * 10 - 1,
			player.coord.y * 10 - 1), fill_pos(player.coord.x * 10 + 1,
			player.coord.y * 10 + 1), rgba_value(50, 50, 255, 255));
}

void	render_all(t_cub *cub)
{
	render_map(cub->render, cub->map);
	render_player(cub->render, cub->player);
	draw_line(cub->render, fill_coord(cub->player.coord.x * 10,
			cub->player.coord.y * 10), fill_coord(cub->player.coord.x * 10
			+ cub->player.dir.x * 10, cub->player.coord.y * 10
			+ cub->player.dir.y * 10), rgba_value(0, 255, 0, 255));
}

void	starting_direction(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir = fill_coord(0, -1);
		p->plane = fill_coord(-0.66, 0);
	}
	else if (c == 'S')
	{
		p->dir = fill_coord(0, 1);
		p->plane = fill_coord(0.66, 0);
	}
	else if (c == 'E')
	{
		p->dir = fill_coord(1, 0);
		p->plane = fill_coord(0, -0.66);
	}
	else
	{
		p->dir = fill_coord(-1, 0);
		p->plane = fill_coord(0, 0.66);
	}
}

char	**get_map(void)
{
	char	**map;

	map = malloc(11 * sizeof(char *));
	map[0] = ft_strdup("111111111111111111");
	map[1] = ft_strdup("100000000000000001");
	map[2] = ft_strdup("100100000000001001");
	map[3] = ft_strdup("100000010000000001");
	map[4] = ft_strdup("111100010000001001");
	map[5] = ft_strdup("100001000000000001");
	map[6] = ft_strdup("100001001111111001");
	map[7] = ft_strdup("111111111000000001");
	map[8] = ft_strdup("100001000000000001");
	map[9] = ft_strdup("111111111111111111");
	map[10] = NULL;
	return (map);
}
