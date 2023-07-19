/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:34 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/19 14:59:52 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_exit(t_cub *cub)
{
	ft_freestr(cub->map);
	// mlx_clear_window(cub->ptr, cub->win);
	// mlx_destroy_window(cub->ptr, cub->win);
	// mlx_destroy_display(cub->ptr);
	free(cub->ptr);
	exit(1);
}

void	game_loop(void *thing)
{
	t_cub	*cub;

	cub = (t_cub*)thing;
	// (void)player;
	render_all(*cub);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_S))
		move_down(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_W))
		move_up(&cub->player, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_Q))
		turn_left(&cub->player);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_E))
		turn_right(&cub->player);
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
	cub.player.coord = fill_coord(60, 60);
	cub.player.rads = PI;
	cub.player.delta = fill_coord(cos(cub.player.rads) * 5, sin(cub.player.rads) * 5);

	mlx_loop_hook(cub.ptr, &game_loop, &cub);
	// mlx_hook(cub.win, 17, 0, ft_exit, &cub);
	mlx_loop(cub.ptr);
	return (0);
}
