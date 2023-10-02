/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:28:54 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/02 15:13:28 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	check_digit_error(char *line)
{
	int	i;
	int	nb_v;

	i = rec_pos_element(line);
	nb_v = 0;
	while (line[i])
	{
		if (line[i] == ',')
			nb_v++;
		if (line[i] == '\n')
			break ;
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if ((line[i] != ',' && !ft_isdigit(line[i])) || nb_v > 2)
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_data_rgb_error(char *line, int i)
{
	int	b;
	int	cmp;

	i = 0;
	cmp = 0;
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			b = 1;
		if ((line[i] == ',' || line[i] == ' ' || line[i] == '\t') && b == 1)
		{
			cmp++;
			b = 0;
		}
		else
			i++;
	}
	if (!line[i] && b == 1)
		cmp++;
	if (cmp != 3)
		return (1);
	return (0);
}