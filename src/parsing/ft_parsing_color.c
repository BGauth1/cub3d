/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:43:51 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/04 13:56:44 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	check_data_rec_rgb(int **col, int j)
{
	int	i;

	i = 0;
	if (j != 3)
		return (1);
	while (i < 3)
	{
		if ((*col)[i] >= 0 && (*col)[i] <= 255)
			i++;
		else
			return (1);
	}
	return (0);
}

static int	ft_check_tmp(char *tmp)
{
	if (!tmp)
		return (-1);
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (-1);
	}
	return (0);
}

static int	ft_init_struct_rgb(int **col, char *line, int start, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (line[i] && j < 3)
	{
		if (line[i] == ',' || line[i] == '\t' || line[i] == ' ' \
			|| (line[i] == '\n' && j == 2))
		{
			tmp = ft_substr(line, start, i - start);
			if (ft_check_tmp(tmp) == -1)
				return (-1);
			(*col)[j] = ft_atois(tmp);
			free(tmp);
			j++;
			while (line[i] && !ft_isdigit(line[i]) && line[i] != '\n')
				i++;
			start = i;
		}
		i++;
	}
	return (j);
}

static int	rec_rgb(char *line, int **col)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (!ft_isdigit(line[i]))
		i++;
	start = i;
	j = ft_init_struct_rgb(col, line, start, i);
	if (j == -1)
		return (1);
	if (check_data_rec_rgb(col, j) == 1)
		return (1);
	return (0);
}

int	parsing_colors(char *line, t_data_fd *data, int id)
{
	int	b;
	int	i;

	i = 0;
	b = check_digit_error(line);
	if (b == 0)
		b = check_data_rgb_error(line, i);
	if (id == 5 && b == 0)
		b = rec_rgb(line, &data->f);
	else if (id == 6 && b == 0)
		b = rec_rgb(line, &data->c);
	if (b == 1)
	{
		printf_error(id, "Wrong data");
		return (1);
	}
	return (0);
}
