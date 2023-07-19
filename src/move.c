/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:59:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/19 15:59:43 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_here(int x, int y, char **map)
{
	return (map[(y - 5) / 40][(x - 5) / 40] == '1' || map[(y + 5) / 40][(x + 5) / 40] == '1' ||
			map[(y + 5) / 40][(x - 5) / 40] == '1' || map[(y - 5) / 40][(x + 5) / 40] == '1');
}

void	turn_left(t_player *p)
{
	p->rads -= 0.05;
	if (p->rads < 0)
		p->rads += 2 * PI;
	p->delta.x = cos(p->rads) * 5;
	p->delta.y = sin(p->rads) * 5;
}

void	turn_right(t_player *p)
{
	p->rads += 0.05;
	if (p->rads > 2 * PI)
		p->rads -= 2 * PI;
	p->delta.x = cos(p->rads) * 5;
	p->delta.y = sin(p->rads) * 5;
}

// float	move_left(t_player *p, char **map)
// {
// 	if (!wall_here(x - 1, y, map))
// 		x -= 0.1;
// 	return (x);
// }

// float	move_right(t_player *p, char **map)
// {
// 	if (!wall_here(x + 1, y, map))
// 		x += 0.1;
// 	return (x);
// }

void	move_up(t_player *p, char **map)
{
	if (!wall_here(p->coord.x + p->delta.x * 0.5, p->coord.y, map))
		p->coord.x += p->delta.x * 0.5;
	if (!wall_here(p->coord.x, p->coord.y + p->delta.y * 0.5, map))
		p->coord.y += p->delta.y * 0.5;
}

void	move_down(t_player *p, char **map)
{
	if (!wall_here(p->coord.x - p->delta.x * 0.5, p->coord.y, map))
		p->coord.x -= p->delta.x * 0.5;
	if (!wall_here(p->coord.x, p->coord.y - p->delta.y * 0.5, map))
		p->coord.y -= p->delta.y * 0.5;
}
