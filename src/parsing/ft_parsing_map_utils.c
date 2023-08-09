/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:25:53 by lamasson          #+#    #+#             */
/*   Updated: 2023/07/31 21:56:25 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_pts_card(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_find_map(char *line)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '0' || line[i] == '1')
		{
			b = 1;
			i++;
		}
		else if (check_pts_card(line[i]))
			i++;
		else
			return (1);
	}
	if (line[i] == '\n' && b == 0)
		return (1);
	return (0);
}

static int	rec_data_map(char *line, int fd, t_data_fd *data)
{
	int	tmp;

	data->input->y = 0;
	data->input->x = ft_strlen(line);
	while (line && ft_find_map(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
		tmp = ft_strlen(line);
		if (tmp > data->input->x)
			data->input->x = tmp;
		data->input->y++;
	}
	if (line)
	{
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		return (1);
	}
	close(fd);
	return (0);
}

int	first_read_map(char *path, t_data_fd *data)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_find_map(line) == 0)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (rec_data_map(line, fd, data) == 1)
	{
		close(fd);
		printf("Error\nInvalid Map\n");
		return (1);
	}
	return (0);
}
