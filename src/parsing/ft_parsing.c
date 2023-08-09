/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:52:55 by lamasson          #+#    #+#             */
/*   Updated: 2023/08/01 20:07:50 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*parsing_intro(char **arg, int argc)
{
	int		fd;
	char	*path;

	if (argc > 2)
	{
		printf("Error\nToo many arguments\n");
		return (NULL);
	}
	else if (argc < 2)
	{
		printf("Error\nNo fd\n");
		return (NULL);
	}
	path = arg[1];
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n%s\n", strerror(errno));
		return (NULL);
	}
	close(fd);
	return (path);
}

static int	ft_parse_line(char *line, t_data_fd *data)
{
	int	b;
	int	id;	

	b = 0;
	id = check_id(line);
	if (check_nb_element(data, id) == 1)
		return (1);
	if (id >= 1 && id <= 4)
		b = parsing_texture(line, data, id);
	else if (id == 5 || id == 6)
		b = parsing_colors(line, data, id);
	else if (id == -2)
		return (0);
	else if (id == -1)
	{
		if (check_if_all_init(data) == 1)
			return (1);
		if (ft_parsing_map(data, line) == 1)
			return (1);
	}
	if (b == 1)
		return (1);
	return (0);
}

static int	recover_file(char *path, t_data_fd *data)
{
	int		fd;
	int		check;
	char	*line;

	check = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line && check != 1)
	{
		check = ft_parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	while (line && check == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check == 1)
		return (1);
	return (0);
}

static int	last_check_map(t_data_fd *data)
{
	if (second_read_map(data))
	{
		ft_free_tab_map(data);
		ft_free_struct(data);
		return (1);
	}
	return (0);
}

int	parsing_data(int argc, char **argv, t_data_fd *data)
{
	char	*path;

	path = parsing_intro(argv, argc);
	if (!path)
		return (1);
	ft_init_struct(data);
	if (first_read_map(path, data))
	{
		ft_free_struct(data);
		return (1);
	}
	ft_init_tab_map(data);
	if (recover_file(path, data))
	{
		ft_free_tab_map(data);
		ft_free_struct(data);
		return (1);
	}
	if (last_check_map(data))
		return (1);
	return (0);
}
