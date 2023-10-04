/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:57:23 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 16:42:04 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_textures(t_color *textures)
{
	if (textures->no_texture)
	{
		if (textures->no_texture->pixels)
			free(textures->no_texture->pixels);
		free(textures->no_texture);
	}
	if (textures->so_texture)
	{
		if (textures->so_texture->pixels)
			free(textures->so_texture->pixels);
		free(textures->so_texture);
	}
	if (textures->ea_texture)
	{
		if (textures->ea_texture->pixels)
			free(textures->ea_texture->pixels);
		free(textures->ea_texture);
	}
	if (textures->we_texture)
	{
		if (textures->we_texture->pixels)
			free(textures->we_texture->pixels);
		free(textures->we_texture);
	}
}

int	ft_exit(t_cub *cub, int n)
{
	if (n == 2 || !n)
	{
		ft_free_tab_map(&cub->data);
		ft_free_struct(&cub->data);
		free_textures(&cub->textures);
	}
	if (!n)
		free(cub->player.rays);
	exit(n);
}
