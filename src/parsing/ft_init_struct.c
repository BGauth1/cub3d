/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:02:42 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/31 22:06:10 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_struct(t_data_fd *data)
{
	if (data->path_no)
		free(data->path_no);
	if (data->path_so)
		free(data->path_so);
	if (data->path_we)
		free(data->path_we);
	if (data->path_ea)
		free(data->path_ea);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
	free(data->input);
}

void	ft_init_struct(t_data_fd *data)
{
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->path_ea = NULL;
	data->f = malloc(sizeof(int) * 3);
	data->c = malloc(sizeof(int) * 3);
	data->f[0] = -1;
	data->c[0] = -1;
	data->input = malloc(sizeof(t_map));
	data->input->j = 0;
	data->input->i = 0;
	data->input->pos_j = 'A';
}

void	ft_free_tab_map(t_data_fd *data)
{
	int	i;

	i = 0;
	while (i < data->input->y)
	{
		if (data->tab[i])
			free(data->tab[i]);
		i++;
	}
	free(data->tab);
}

void	ft_init_tab_map(t_data_fd *data)
{
	int	i;

	i = 0;
	data->tab = malloc(sizeof(char *) * (data->input->y + 1));
	while (i < data->input->y)
	{
		data->tab[i] = malloc(sizeof(char) * (data->input->x + 1));
		i++;
	}
	data->tab[i] = NULL;
}
