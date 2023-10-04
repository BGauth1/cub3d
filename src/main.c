/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:34 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 16:47:50 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	game_loop(void *thing)
{
	t_cub	*cub;

	cub = (t_cub *)thing;
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
	get_rays(cub, cub->player.rays);
}

static void	starting_direction(t_player *p, char c)
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

static int	init_cub(t_cub *cub, int argc, char **argv)
{
	int			i;
	t_data_fd	data;

	if (parsing_data(argc, argv, &data))
		return (1);
	cub->data = data;
	cub->map = data.tab;
	cub->ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	load_textures(cub);
	if (!cub->textures.ea_texture || !cub->textures.so_texture
		|| !cub->textures.no_texture || !cub->textures.we_texture)
		return (2);
	cub->render = mlx_new_image(cub->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(cub->ptr, cub->render, 0, 0);
	cub->player.coord = fill_coord(data.input->pos_s[0] + 0.5,
			data.input->pos_s[1] + 0.5);
	starting_direction(&cub->player, cub->data.input->pos_j);
	cub->textures.c_color = rgba_value(data.c[0], data.c[1], data.c[2], 255);
	cub->textures.f_color = rgba_value(data.f[0], data.f[1], data.f[2], 255);
	cub->player.rays = malloc((WIN_WIDTH) * sizeof(t_ray));
	i = -1;
	while (++i < WIN_WIDTH)
		cub->player.rays[i].num = WIN_WIDTH - i - 1;
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;
	int		err;

	err = init_cub(&cub, ac, av);
	if (err)
		ft_exit(&cub, err);
	mlx_loop_hook(cub.ptr, game_loop, &cub);
	mlx_loop(cub.ptr);
	mlx_terminate(cub.ptr);
	ft_exit(&cub, 0);
	return (0);
}
