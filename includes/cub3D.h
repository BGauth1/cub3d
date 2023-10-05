/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:47 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/05 18:11:27 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define WIN_WIDTH	800
# define WIN_HEIGHT	800

# define K_ESC		65307
# define K_LEFT		65361
# define K_RIGHT	65363
# define K_UP		65362
# define K_DOWN		65364

# define K_Q		113
# define K_E		101

# define M_SCRL_UP	4
# define M_SRCL_DWN	5

# define P_HITBOX	0.125
# define P_MV_SPEED	0.01

# define PI			3.141592

typedef struct s_data_fd
{
	char			**tab;
	struct s_map	*input;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				*f;
	int				*c;
}				t_data_fd;

typedef struct s_map
{
	int		x;
	int		y;
	int		j;
	int		i;
	int		m;
	int		pos_s[2];
	char	pos_j;
}				t_map;

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_coord
{
	float	x;
	float	y;
}				t_coord;

typedef struct s_texture
{
	int	*pixels;
	int	width;
	int	height;
}				t_texture;

typedef struct s_color
{
	t_texture	*no_texture;
	t_texture	*so_texture;
	t_texture	*we_texture;
	t_texture	*ea_texture;
	int			c_color;
	int			f_color;
}				t_color;

typedef struct s_ray
{
	int		num;
	t_coord	dir;
	t_coord	side_dist;
	t_coord	delta_dist;
	float	wall_dist;
	float	wallx;
	t_pos	step;
	int		hit;
	int		side;
}				t_ray;

typedef struct s_player
{
	t_pos	pos;
	t_coord	coord;
	t_coord	dir;
	t_coord	plane;
	t_ray	*rays;
	float	move_speed;
}				t_player;

typedef struct s_cub
{
	t_player	player;
	t_color		textures;
	mlx_image_t	*render;
	mlx_t		*ptr;
	t_data_fd	data;
	void		*win;
	int			width;
	int			height;
	char		**map;
}				t_cub;

//	ft_parsing.c	//
int			parsing_data(int argc, char **argv, t_data_fd *data);

//	ft_parsing_color.c	//
int			parsing_colors(char *line, t_data_fd *data, int id);

//	ft_parsing_color_error.c	//
int			check_digit_error(char *line);
int			check_data_rgb_error(char *line, int i);
int			check_path_file(char *path, char *format);

//	ft_parse_line_break.c	//
int			ft_parse_line_split(char *line, t_data_fd *data);

//	ft_parsing_texture.c	//
int			check_fake(char *line);
int			rec_pos_element(char *line);
int			check_id(char *line);
int			parsing_texture(char *line, t_data_fd *data, int id);

//	ft_parsing_texture_error.c	//
int			printf_error(int id, char *str);
int			check_end_line_texture(char *line, int i, char *path, int len);
int			check_path_texture(char *path, int id);
int			check_nb_element(t_data_fd *data, int id);
int			check_if_all_init(t_data_fd *data, char *line);

//	ft_init_struct.c	//
void		ft_free_struct(t_data_fd *data);
void		ft_init_struct(t_data_fd *data);
void		ft_init_tab_map(t_data_fd *data);
void		ft_free_tab_map(t_data_fd *data);

//	ft_parsing_map.c	//
int			ft_find_map(char *line);
int			ft_parsing_map(t_data_fd *data, char *line);

//	ft_parsing_map_utils.c	//
int			first_read_map(char *path, t_data_fd *data);
int			check_pts_card(char c);
int			ft_complet_map(char *line);

//	ft_parsing_map_error.c	//
int			second_read_map(t_data_fd *data);

//	dda.c	//
void		get_rays(t_cub *cub, t_ray *rays);

//	draw.c	//
int			rgba_value(int r, int g, int b, int a);
void		draw_single_ray(t_cub *cub, t_ray ray, int col);

//	free.c	//
int			ft_exit(t_cub *cub, int n);

//	hooks.c	//
void		turn_left(t_player *p);
void		turn_right(t_player *p);

//	move.c	//
void		move_right(t_player *p, char **map);
void		move_left(t_player *p, char **map);
void		move_down(t_player *p, char **map);
void		move_up(t_player *p, char **map);

//	texture.c	//
t_texture	*get_side_texture(int side, float dirx, float diry,
				t_color texture);
void		load_textures(t_cub *cub);

//	utils.c	//
t_coord		fill_coord(float x, float y);
t_pos		fill_pos(int x, int y);
int			ft_abs(int i);
float		ft_fabs(float x);

#endif
