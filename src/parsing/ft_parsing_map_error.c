/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:36:04 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/02 15:25:45 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_pos_player(t_data_fd *data)
{
	if (data->input->pos_j == 'A')
	{
		printf("Error\nNo position for the player on the map\n");
		return (1);
	}
	return (0);
}

static int	check_near_zero(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

static int	check_pos_inside_map(t_data_fd *data, int j, int i)
{
	if (i == 0 || i + 1 == data->input->x)
		return (1);
	else if (j == 0 || j + 1 == data->input->y)
		return (1);
	else if (check_near_zero(data->tab[j][i - 1]))
		return (1);
	else if (check_near_zero(data->tab[j][i + 1]))
		return (1);
	else if (check_near_zero(data->tab[j - 1][i]))
		return (1);
	else if (check_near_zero(data->tab[j + 1][i]))
		return (1);
	return (0);
}	

static int	char_by_char(t_data_fd *data, int j, int i)
{
	while (data->tab[j][i])
	{
		if (data->tab[j][i] == '0')
		{
			if (!check_pos_inside_map(data, j, i))
				i++;
			else
				return (1);
		}
		else if (data->tab[j][i] == ' ')
			i++;
		else if (data->tab[j][i] == '1')
			i++;
		else if (check_pts_card(data->tab[j][i]))
		{
			if (!check_pos_inside_map(data, j, i))
				i++;
			else
				return (2);
		}
		else
			return (1);
	}
	return (0);
}

int	second_read_map(t_data_fd *data)
{
	int	i;
	int	j;
	int	error;

	i = 0;
	j = 0;
	error = 0;
	if (check_pos_player(data) == 1)
		return (1);
	while (data->tab[j])
	{
		error = char_by_char(data, j, i);
		if (error == 1)
			printf("Error\nInvalid Map\n");
		else if (error == 2)
			printf("Error\nWrong position player\n");
		if (error > 0)
			return (1);
		j++;
		i = 0;
	}
	return (0);
}
