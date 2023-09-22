/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:19:07 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 19:20:49 by gbertet          ###   ########.fr       */
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
		fill_pos(399, 399), rgba_value(0, 0, 0, 255));
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				color = rgba_value(255, 0, 0, 255);
			else
				color = rgba_value(0, 0, 0, 255);
			draw_rectangle(img, fill_pos(j * 40, i * 40),
				fill_pos((j + 1) * 40 - 1, (i + 1) * 40 - 1), color);
		}
	}
}

void	render_player(mlx_image_t *img, t_player player)
{
	draw_rectangle(img, fill_pos(player.coord.x * 40 - 5,
			player.coord.y * 40 - 5), fill_pos(player.coord.x * 40 + 5,
			player.coord.y * 40 + 5), rgba_value(50, 50, 255, 255));
}

void	render_all(t_cub *cub)
{
	render_map(cub->render, cub->map);
	render_player(cub->render, cub->player);
	draw_line(cub->render, fill_coord(cub->player.coord.x * 40,
			cub->player.coord.y * 40), fill_coord(cub->player.coord.x * 40
			+ cub->player.dir.x * 25, cub->player.coord.y * 40
			+ cub->player.dir.y * 25), rgba_value(0, 255, 0, 255));
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
