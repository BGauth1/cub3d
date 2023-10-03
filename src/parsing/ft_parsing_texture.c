/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:02:23 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/03 16:25:22 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_fake(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t' \
			&& line[i] != '1' && line[i] != '0' && !check_pts_card(line[i]))
		{
			printf("Error\nIncorrect data in file\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_id(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (-2);
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
			return (1);
		if (line[i] == 'S' && line[i + 1] == 'O')
			return (2);
		if (line[i] == 'W' && line[i + 1] == 'E')
			return (3);
		if (line[i] == 'E' && line[i + 1] == 'A')
			return (4);
		if (line[i] == 'F')
			return (5);
		if (line[i] == 'C')
			return (6);
		i++;
	}
	return (-1);
}

int	rec_pos_element(char *line)
{
	int	i;

	i = 0;
	while (!ft_isalpha(line[i]))
		i++;
	while (ft_isalpha(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static char	*rec_path_text(char *line)
{
	int		i;
	int		start;
	char	*path;

	i = rec_pos_element(line);
	start = i;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			break ;
		i++;
	}
	path = ft_substr(line, start, i - start);
	if (!path)
		exit (1);
	if (check_end_line_texture(line, i, path, (i - start) - 4) == 1)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

int	parsing_texture(char *line, t_data_fd *data, int id)
{
	char	*path;

	path = rec_path_text(line);
	if (id == 1)
		data->path_no = path;
	else if (id == 2)
		data->path_so = path;
	else if (id == 3)
		data->path_we = path;
	else if (id == 4)
		data->path_ea = path;
	if (!path)
	{
		printf_error(id, "Wrong data");
		return (1);
	}
	if (check_path_texture(path, id) == 1)
		return (1);
	return (0);
}
