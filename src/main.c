/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:34 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/07 13:52:06 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(t_cub *cub)
{
	ft_freestr(cub->map);
	free(cub->ptr);
	exit(1);
}

void	game_loop(void *thing)
{
	t_cub	*cub;

	cub = (t_cub*)thing;
	if (cub->key.m)
		render_all(cub);
	draw_rays(cub);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_S))
		move_down(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_W))
		move_up(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_A))
		move_left(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_D))
		move_right(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_LEFT))
		turn_left(&cub->player);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_RIGHT))
		turn_right(&cub->player);
	printf("FPS: %d\n", (int)(1 / cub->ptr->delta_time));
	// if (cub->key.right)
	// 	cub->player.coord.x = move_right(cub->player.coord.x, cub->player.coord.y, cub->map);
	// if (cub->key.left)
	// 	cub->player.coord.x = move_left(cub->player.coord.x, cub->player.coord.y, cub->map);
	// printf("caac\n");
}

int	main(int ac, char **av)
{
	t_cub	cub;

	(void) av;
	cub.width = WIN_WIDTH;
	cub.height = WIN_HEIGHT;
	if (ac < 2)
	{
		ft_putstr_fd("Too few arguments !", 2);
		ft_exit(&cub);
	}
	cub.ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	cub.render = mlx_new_image(cub.ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(cub.ptr, cub.render, 0, 0);
	cub.map = get_map();
	cub.player.coord = fill_coord(2, 2);
	cub.player.rads = PI;
	cub.player.dir = fill_coord(-1, 0);
	cub.player.plane.x = 0;
	cub.player.plane.y = 0.66;
	cub.textures.ceiling_color = rgba_value(228, 228, 118, 255);
	cub.textures.floor_color = rgba_value(203, 203, 90, 255);
	init_keypress(&cub);
	mlx_loop_hook(cub.ptr, game_loop, &cub);
	mlx_key_hook(cub.ptr, &da_key_hook, &cub);
	mlx_loop(cub.ptr);
	mlx_terminate(cub.ptr);
	return (0);
}
