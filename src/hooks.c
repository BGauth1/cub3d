/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:29 by gbertet           #+#    #+#             */
/*   Updated: 2023/08/02 16:09:00 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_keypress(t_cub *cub)
{
    cub->key.m = 0;
}

void	da_key_hook(mlx_key_data_t keydata, void *thing)
{
    t_cub   *cub;

    cub = thing;
    if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
        cub->key.m = (cub->key.m != 1);
}