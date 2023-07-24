/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:32:02 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/24 14:02:00 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_freestr(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}

int ft_abs(int i)
{
    if (i < 0)
        return (i * -1);
    return (i);
}

void    ft_fswap(float *a, float *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
