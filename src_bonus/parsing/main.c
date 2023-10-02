/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:00:55 by lamasson          #+#    #+#             */
/*   Updated: 2023/09/29 17:31:55 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

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
	
	
	
	ft_free_tab_map(&data);
	ft_free_struct(&data);
	return (0);
}
//parsing map ' ' par /0 remplacer condition par taille x et y 
