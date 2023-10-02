/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:00:55 by lamasson          #+#    #+#             */
/*   Updated: 2023/10/02 15:15:43 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_data_fd	data;
	int			i;

	i = 0;
	if (parsing_data(argc, argv, &data))
		return (1);
	
	
	
	while (i < data.input->y)
	{
		printf("%s \n", data.tab[i]);
		i++;
	}
	printf(" x = %d\n y = %d\n", data.input->pos_s[0], data.input->pos_s[1]);
	printf(" %d - %d - %d\n", data.f[0], data.f[1], data.f[2]);
	printf(" %d - %d - %d\n", data.c[0], data.c[1], data.c[2]);
	
	ft_free_tab_map(&data);
	ft_free_struct(&data);
	return (0);
}
//parsing map ' ' par /0 remplacer condition par taille x et y 
