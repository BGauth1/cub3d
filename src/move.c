/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:59:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/02 17:33:11 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	hit_wall(float x, float y, char **map)
{
	return (map[(int)(y - P_HITBOX)][(int)(x - P_HITBOX)] == '1'
			|| map[(int)(y + P_HITBOX)][(int)(x + P_HITBOX)] == '1'
			|| map[(int)(y + P_HITBOX)][(int)(x - P_HITBOX)] == '1'
			|| map[(int)(y - P_HITBOX)][(int)(x + P_HITBOX)] == '1');
}

void	move_left(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(p->coord.x + p->dir.y * p->move_speed, p->coord.y, map))
			p->coord.x += p->dir.y * p->move_speed;
		if (!hit_wall(p->coord.x, p->coord.y - p->dir.x * p->move_speed, map))
			p->coord.y -= p->dir.x * p->move_speed;
	}
}

void	move_right(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(p->coord.x - p->dir.y * p->move_speed, p->coord.y, map))
			p->coord.x -= p->dir.y * p->move_speed;
		if (!hit_wall(p->coord.x, p->coord.y + p->dir.x * p->move_speed, map))
			p->coord.y += p->dir.x * p->move_speed;
	}
}

void	move_up(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(p->coord.x + p->dir.x * p->move_speed, p->coord.y, map))
			p->coord.x += p->dir.x * p->move_speed;
		if (!hit_wall(p->coord.x, p->coord.y + p->dir.y * p->move_speed, map))
			p->coord.y += p->dir.y * p->move_speed;
	}
}

void	move_down(t_player *p, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(p->coord.x - p->dir.x * p->move_speed, p->coord.y, map))
			p->coord.x -= p->dir.x * p->move_speed;
		if (!hit_wall(p->coord.x, p->coord.y - p->dir.y * p->move_speed, map))
			p->coord.y -= p->dir.y * p->move_speed;
	}
}
