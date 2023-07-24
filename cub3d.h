/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:47 by gbertet           #+#    #+#             */
/*   Updated: 2023/07/24 15:09:04 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"

# define WIN_WIDTH	400
# define WIN_HEIGHT	400

# define K_ESC		65307
# define K_LEFT		65361
# define K_RIGHT	65363
# define K_UP		65362
# define K_DOWN		65364

# define K_Q		113
# define K_E		101

# define M_SCRL_UP	4
# define M_SRCL_DWN	5

# define PI			3.141592

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_keypress
{
	int up;
	int down;
	int	left;
	int	right;
	int	q;
	int	e;
}				t_keypress;

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_coord
{
	float	x;
	float	y;
}				t_coord;

typedef struct	s_color
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		ceiling_color;
	int		floor_color;
}				t_color;

typedef struct	s_player
{
	t_coord	coord;
	t_coord	delta;
	float	rads;
}				t_player;

typedef struct	s_cub
{
	t_player	player;
	t_keypress	key;
	mlx_image_t	*render;
	mlx_t		*ptr;
	void		*win;
	int			width;
	int			height;
	char		**map;
}				t_cub;

t_coord	fill_coord(float x, float y);
t_pos	fill_pos(int x, int y);
void	draw_line(mlx_image_t *data, t_coord begin, t_coord end, int color);
void	draw_rectangle(mlx_image_t *data, t_pos begin, t_pos end, int color);
int		rgba_value(int r, int g, int b, int a);
int		ft_exit(t_cub *cub);
char	**get_map();
void	render_all(t_cub *cub);
int 	ft_abs(int i);
void    ft_freestr(char **str);
void    ft_fswap(float *a, float *b);
t_keypress	init_key();


void	turn_left(t_player *p);
void	turn_right(t_player *p);
float	move_right(float x, float y, char **map);
float	move_left(float x, float y, char **map);
void	move_down(t_player *p, char **map);
void	move_up(t_player *p, char **map);

#endif
