/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:25:53 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/05 00:01:16 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_pts_card(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_complet_map(char *line)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ')
			b = 1;
		else if (line[i] != '\t' && !check_pts_card(line[i]))
			return (1);
		i++;
	}
	if (line[i] == '\n' && b == 0)
		return (1);
	return (0);
}

static int	check_last_line_map(char *line, int fd)
{
	int	b;
	int	i;

	b = 0;
	i = 0;
	while (line)
	{
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n')
				b = 1;
			i++;
		}
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
	if (b == 1)
		return (1);
	return (0);
}

static int	rec_data_map(char *line, int fd, t_data_fd *data)
{
	int	tmp;

	data->input->y = 0;
	data->input->x = ft_strlen(line);
	while (line && ft_complet_map(line) == 0)
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
		if (check_last_line_map(line, fd))
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
