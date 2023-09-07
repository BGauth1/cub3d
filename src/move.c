/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:59:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/08/02 19:05:05 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_here(float x, float y, char **map)
{
	return (map[(int)(y - 0.125)][(int)(x - 0.125)] == '1' || map[(int)(y + 0.125)][(int)(x + 0.125)] == '1' ||
			map[(int)(y + 0.125)][(int)(x - 0.125)] == '1' || map[(int)(y - 0.125)][(int)(x + 0.125)] == '1');
}

void	turn_left(t_player *p)
{
	float	olddirx;
	float	oldplanex;
	
	p->rads -= 0.05;
	if (p->rads < 0)
		p->rads += 2 * PI;
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

	p->rads += 0.05;
	if (p->rads > 2 * PI)
		p->rads -= 2 * PI;
	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(0.03) - p->dir.y * sin(0.03);
	p->dir.y = olddirx * sin(0.03) + p->dir.y * cos(0.03);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(0.03) - p->plane.y * sin(0.03);
	p->plane.y = oldplanex * sin(0.03) + p->plane.y * cos(0.03); 
}

void	move_left(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!wall_here(p->coord.x + p->dir.y * 0.01, p->coord.y, map))
			p->coord.x += p->dir.y * 0.01;
		if (!wall_here(p->coord.x, p->coord.y - p->dir.x * 0.01, map))
			p->coord.y -= p->dir.x * 0.01;
	}
}

void	move_right(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!wall_here(p->coord.x - p->dir.y * 0.01, p->coord.y, map))
			p->coord.x -= p->dir.y * 0.01;
		if (!wall_here(p->coord.x, p->coord.y + p->dir.x * 0.01, map))
			p->coord.y += p->dir.x * 0.01;
	}
}

void	move_up(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!wall_here(p->coord.x + p->dir.x * 0.01, p->coord.y, map))
			p->coord.x += p->dir.x * 0.01;
		if (!wall_here(p->coord.x, p->coord.y + p->dir.y * 0.01, map))
			p->coord.y += p->dir.y * 0.01;
	}
}

void	move_down(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!wall_here(p->coord.x - p->dir.x * 0.01, p->coord.y, map))
			p->coord.x -= p->dir.x * 0.01;
		if (!wall_here(p->coord.x, p->coord.y - p->dir.y * 0.01, map))
			p->coord.y -= p->dir.y * 0.01;
	}
}
