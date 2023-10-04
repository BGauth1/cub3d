/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:29 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/02 17:26:39 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	turn_left(t_player *p)
{
	float	olddirx;
	float	oldplanex;

	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(-0.03) - p->dir.y * sin(-0.03);
	p->dir.y = olddirx * sin(-0.03) + p->dir.y * cos(-0.03);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(-0.03) - p->plane.y * sin(-0.03);
	p->plane.y = oldplanex * sin(-0.03) + p->plane.y * cos(-0.03);
}

void	turn_right(t_player *p)
{
	float	olddirx;
	float	oldplanex;

	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(0.03) - p->dir.y * sin(0.03);
	p->dir.y = olddirx * sin(0.03) + p->dir.y * cos(0.03);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(0.03) - p->plane.y * sin(0.03);
	p->plane.y = oldplanex * sin(0.03) + p->plane.y * cos(0.03);
}
