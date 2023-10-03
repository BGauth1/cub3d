/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_texture_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:37:29 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/03 16:11:20 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	printf_error(int id, char *str)
{
	if (id == 1)
		printf("Error\n%s for element NO\n", str);
	else if (id == 2)
		printf("Error\n%s for element SO\n", str);
	else if (id == 3)
		printf("Error\n%s for element WE\n", str);
	else if (id == 4)
		printf("Error\n%s for element EA\n", str);
	else if (id == 5)
		printf("Error\n%s for element F\n", str);
	else if (id == 6)
		printf("Error\n%s for element C\n", str);
	return (1);
}

int	check_end_line_texture(char *line, int i, char *path, int j)
{
	char	*format;
	int		k;

	format = ".png";
	k = 0;
	while (path[j])
	{
		if (path[j] == format[k])
		{
			j++;
			k++;
		}
		else
			return (1);
	}
	if (line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_path_texture(char *path, int id)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf_error(id, "Wrong path");
		return (1);
	}
	close(fd);
	return (0);
}

int	check_nb_element(t_data_fd *data, int id)
{
	int	b;

	b = 0;
	if (id == 1 && data->path_no)
		b = 1;
	else if (id == 2 && data->path_so)
		b = 1;
	else if (id == 3 && data->path_we)
		b = 1;
	else if (id == 4 && data->path_ea)
		b = 1;
	else if (id == 5 && data->f[0] != -1)
		b = 1;
	else if (id == 6 && data->c[0] != -1)
		b = 1;
	else
		return (0);
	if (b == 1)
		printf_error(id, "Too many arguments");
	return (1);
}

int	check_if_all_init(t_data_fd *data, char *line)
{
	int	id;

	id = 0;
	if (check_fake(line))
		return (1);
	if (!data->path_no)
		id = 1;
	else if (!data->path_so)
		id = 2;
	else if (!data->path_we)
		id = 3;
	else if (!data->path_ea)
		id = 4;
	else if (data->f[0] == -1)
		id = 5;
	else if (data->c[0] == -1)
		id = 6;
	if (id != 0)
	{
		printf_error(id, "No data");
		return (1);
	}
	return (0);
}
