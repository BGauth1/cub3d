/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line_break.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:48:52 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/05 21:09:19 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	ft_line_data(char *line, t_data_fd *data, int id)
{
	int	b;

	b = 0;
	if (id >= 1 && id <= 4)
		b = parsing_texture(line, data, id);
	else if (id == 5 || id == 6)
		b = parsing_colors(line, data, id);
	else if (id == -1)
	{
		if (check_if_all_init(data, line))
			return (1);
		if (!ft_find_map(line))
		{
			data->input->m = 1;
			if (ft_parsing_map(data, line))
				return (1);
		}
	}
	else if (id == -2)
		return (0);
	if (b == 1)
		return (1);
	return (0);
}

int	ft_parse_line_split(char *line, t_data_fd *data)
{
	int	id;

	id = check_id(line);
	if (check_nb_element(data, id) == 1)
		return (1);
	if (data->input->m == 1)
	{
		if (ft_parsing_map(data, line))
			return (1);
	}
	else if (ft_line_data(line, data, id))
		return (1);
	else if (id == -2)
		return (0);
	return (0);
}
