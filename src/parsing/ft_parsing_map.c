/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:29:25 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/31 22:17:30 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_input_pos_player(t_data_fd *data, char *line, int i)
{
	if (check_pts_card(line[i]))
	{	
		if (data->input->pos_j != 'A')
			return (1);
		data->input->pos_j = line[i];
		data->input->pos_s[0] = i;
		data->input->pos_s[1] = data->input->j;
		data->tab[data->input->j][data->input->i] = line[i];
	}
	return (0);
}

static int	ft_fill_tab_map(t_data_fd *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
			data->tab[data->input->j][data->input->i] = ' ';
		else if (ft_input_pos_player(data, line, i) == 1)
			return (1);
		else
			data->tab[data->input->j][data->input->i] = line[i];
		data->input->i++;
		i++;
	}
	data->tab[data->input->j][data->input->i] = '\0';
	return (0);
}

int	ft_parsing_map(t_data_fd *data, char *line)
{
	if (ft_find_map(line) == 1)
		return (0);
	if (ft_fill_tab_map(data, line) == 1)
	{
		printf("Error\nToo many positions for the player on the map\n");
		return (1);
	}
	data->input->j++;
	data->input->i = 0;
	return (0);
}
