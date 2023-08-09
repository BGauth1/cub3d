/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_color_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:28:54 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/29 20:19:06 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	check_end_line_rgb(char *line, int i, int cmp)
{
	if (line[i] == '\0' && cmp != 2)
		return (1);
	if (line[i] && cmp != 3)
		return (1);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	len_digit_rgb(char c, int cmp)
{
	if (c == ',')
		return (1);
	else if (c == ' ' && cmp == 2)
		return (1);
	else if (c == '\t' && cmp == 2)
		return (1);
	return (0);
}

int	check_data_rgb_error(char *line, int i)
{
	int	b;
	int	cmp;

	b = 0;
	cmp = 0;
	while (!ft_isdigit(line[i]))
		i++;
	while (line[i])
	{
		if ((line[i] == ' ' && cmp == 3) || (line[i] == '\t' && cmp == 3))
			break ;
		if (ft_isdigit(line[i]))
			b = 1;
		if (len_digit_rgb(line[i], cmp) && b == 1)
		{
			cmp++;
			b = 0;
		}
		else
			i++;
	}
	if (check_end_line_rgb(line, i, cmp) == 1)
		return (1);
	return (0);
}
