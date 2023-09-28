/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:29 by gbertet           #+#    #+#             */
/*   Updated: 2023/09/28 19:21:45 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_keypress(t_cub *cub)
{
	cub->key.m = 0;
}

void	da_key_hook(mlx_key_data_t keydata, void *thing)
{
	t_cub	*cub;

	cub = thing;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		cub->key.m = (cub->key.m != 1);
}

void	turn_left(t_player *p)
{
	float	olddirx;
	float	oldplanex;

	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(-0.03) - p->dir.y * sin(-0.03);
	p->dir.y = olddirx * sin(-0.03) + p->dir.y * cos(-0.03);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(-0.03) - p->plane.y * sin(-0.03);
	p->plane.y = oldplanex * sin(-0.03) + p->plane.y * cos(-0.03);
}

void	turn_right(t_player *p)
{
	float	olddirx;
	float	oldplanex;

	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(0.03) - p->dir.y * sin(0.03);
	p->dir.y = olddirx * sin(0.03) + p->dir.y * cos(0.03);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(0.03) - p->plane.y * sin(0.03);
	p->plane.y = oldplanex * sin(0.03) + p->plane.y * cos(0.03);
}
