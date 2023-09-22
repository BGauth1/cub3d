/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:34 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/22 21:51:50 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_exit(t_cub *cub)
{
	ft_free_tab_map(&cub->data);
	ft_free_struct(&cub->data);
	// ft_freestr(cub->map);
	free_textures(&cub->textures);
	free(cub->player.rays);
	exit(0);
}

void	game_loop(void *thing)
{
	t_cub	*cub;

	cub = (t_cub *)thing;
	if (cub->key.m)
		render_all(cub);
	draw_rays(cub);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_LEFT_SHIFT))
		cub->player.move_speed = P_MV_SPEED * 1.70;
	else 
		cub->player.move_speed = P_MV_SPEED;
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
	if (mlx_is_key_down(cub->ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cub->ptr);
	printf("FPS: %d\n", (int)(1 / cub->ptr->delta_time));
}

int	init_cub(t_cub *cub, int argc, char **argv)
{
	int	i;
	t_data_fd	data;

	if (parsing_data(argc, argv, &data))
		return (0);
	cub->data = data;
	cub->map = data.tab;
	cub->width = WIN_WIDTH;
	cub->height = WIN_HEIGHT;
	cub->ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	cub->render = mlx_new_image(cub->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(cub->ptr, cub->render, 0, 0);
	// cub->map = get_map();
	cub->player.coord = fill_coord(cub->data.input->pos_s[0], cub->data.input->pos_s[1]);
	cub->player.dir = fill_coord(-1, 0);
	cub->player.plane.x = 0;
	cub->player.plane.y = 0.66;
	cub->textures.ceiling_color = rgba_value(228, 228, 118, 255);
	cub->textures.floor_color = rgba_value(203, 203, 90, 255);
	cub->player.rays = malloc((WIN_WIDTH) * sizeof(t_ray));
	i = -1;
	while (++i < WIN_WIDTH)
		cub->player.rays[i].num = WIN_WIDTH - i - 1;
	get_textures(cub, &cub->textures);
	init_keypress(cub);
	if (!cub->textures.ea_texture || !cub->textures.so_texture
		|| !cub->textures.no_texture || !cub->textures.we_texture)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (!init_cub(&cub, ac, av))
		exit (1);
	draw_texture(&cub, *cub.textures.ea_texture, fill_pos(10, 10));
	mlx_loop_hook(cub.ptr, game_loop, &cub);
	mlx_key_hook(cub.ptr, &da_key_hook, &cub);
	mlx_loop(cub.ptr);
	mlx_terminate(cub.ptr);
	ft_exit(&cub);
	return (0);
}
