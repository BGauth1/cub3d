/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:46:30 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/03 16:43:18 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_texture	*get_side_texture(int side, float dirx, float diry, t_color txtr)
{
	if (side == 1 && diry > 0)
		return (txtr.so_texture);
	else if (side == 0 && dirx > 0)
		return (txtr.ea_texture);
	else if (side == 1)
		return (txtr.no_texture);
	return (txtr.we_texture);
}

static t_texture	*get_texture_from_mlx(mlx_image_t *tmp)
{
	t_texture	*texture;
	int			tot_pixels;
	int			hpos;
	int			bpos;

	if (!tmp)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->pixels = malloc ((tmp->height * tmp->width) * sizeof(int));
	if (!texture->pixels)
		return (NULL);
	texture->height = tmp->height;
	texture->width = tmp->width;
	hpos = -1;
	bpos = 0;
	tot_pixels = tmp->height * tmp->width * 4;
	while (bpos < tot_pixels)
	{
		texture->pixels[++hpos] = rgba_value(tmp->pixels[bpos], tmp->pixels
			[bpos + 1], tmp->pixels[bpos + 2], tmp->pixels[bpos + 3]);
		bpos += 4;
	}
	return (texture);
}

static t_texture	*get_texture(t_cub *cub, char *path)
{
	t_texture		*texture;
	mlx_texture_t	*mlx_texture_tmp;
	mlx_image_t		*mlx_image_tmp;

	mlx_texture_tmp = mlx_load_png(path);
	if (mlx_texture_tmp)
	{
		mlx_image_tmp = mlx_texture_to_image(cub->ptr, mlx_texture_tmp);
		texture = get_texture_from_mlx(mlx_image_tmp);
		mlx_delete_texture(mlx_texture_tmp);
		mlx_delete_image(cub->ptr, mlx_image_tmp);
		return (texture);
	}
	ft_printf("MLX42: Couldn't load \"%s\".\n", path);
	return (NULL);
}

void	load_textures(t_cub *cub)
{
	cub->textures.no_texture = get_texture(cub, cub->data.path_no);
	cub->textures.so_texture = get_texture(cub, cub->data.path_so);
	cub->textures.ea_texture = get_texture(cub, cub->data.path_ea);
	cub->textures.we_texture = get_texture(cub, cub->data.path_we);
}
