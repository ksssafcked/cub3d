/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:49:26 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:07:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# define LENGTH 800
# define HEIGHT 600

/*		structs		*/

typedef struct s_texture
{
	void			*img;
	int				*addr;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_view
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			permawall_dist;
	double			wall_x;
	double			tex_pos;
	double			step;
	int				tex_x;
	int				tex_y;
	t_texture		*tex;
}					t_view;

typedef struct s_map
{
	char			*coor;
	int				length;
	struct s_map	*next;
}					t_map;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	char			direction;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_game
{
	t_map			*map;
	t_player		*player;
	size_t			length_max;
	size_t			height_max;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	t_texture		tex_no;
	t_texture		tex_so;
	t_texture		tex_we;
	t_texture		tex_ea;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				no_defined;
	int				so_defined;
	int				we_defined;
	int				ea_defined;
	int				f_defined;
	int				c_defined;
}					t_game;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
	int				error;
}					t_point;

typedef struct s_vector
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_vector;

typedef struct t_map_utils
{
	char			**map;
	t_point			**point;
	t_point			*start;
	int				height;
	int				width;
	void			*mlx;
	void			*window;
	void			*img;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	int				far;
	struct s_game	*game;
	int				key_w;
	int				key_s;
	int				key_a;
	int				key_d;
	int				key_left;
	int				key_right;
}					t_map_utils;

/*		parser.c	*/

t_game				*game_parser(char *file);
void				*free_map(t_map *map);
void				draw_map(t_map_utils *window, t_game *game);

/*     parser_config.c   */

int					parse_config_line(char *line, t_game *game);

/*     ft_utils.c   */

int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
int					ft_atoi(const char *str);
char				*ft_strchr(const char *str, int c);

/*		ft_split.c   */

char				**ft_split(char const *str, char c);
void				free_split(char **split);

/*    print_map.c   */

int					close_all(t_map_utils *cub);

void				draw_3d_view(t_map_utils *cub);

/*		main.c		*/
void				free_all(t_map_utils *cub);

/*		change.c	*/
void				change_dist(t_view *view);
void				change_side(t_map_utils *cub, t_view *view);
void				change_draw(t_view *view);
void				change_values(t_view *view);
void				change_wall(t_view *view);

/*		raycasting.h	*/
void				set_pixel_color(t_map_utils *cub, int x, int y,
						unsigned int color);
void				init_player_pos(t_map_utils *cub, t_view *view);
void				draw_3d(t_map_utils *cub, t_view *view);
void				draw_3d_view(t_map_utils *cub);

/*		init.c		*/
t_map_utils			*map_init(void);
void				init_image(t_map_utils *cub);
t_map_utils			*init_textures(t_map_utils *cub);
t_map_utils			*init_cub(t_game *game);

/*		direction.h		*/
int					change_dir(t_map_utils *cub);
int					is_wall(t_map_utils *cub, double x, double y);

/*		parser_config.c		*/
void				trim_end(char **str);
int					change_color(char **split_comma, char *line, t_game *game);
int					parse_color(char *line, t_game *game);
int					parse_config_line(char *line, t_game *game);

/*		parser_utils.c	*/
char				*strcpy_no_nl(t_game *game, char *source, char *dest,
						int size);
void				printer_map(char **map);

/*		parser_textures	*/
int					parse_north_south(char **split, t_game *game);
int					parse_east_west(char **split, t_game *game);
int					parse_texture(char *line, t_game *game);

/*		get_info.c	*/
double				get_angle(char c);
void				get_player_pos(t_game *game);
char				**get_full_map(t_game *game);
int					get_texture(t_map_utils *cub, t_view *view);

/*		handle.c	*/
int					close_all(t_map_utils *cub);
int					key_release(int keycode, t_map_utils *cub);
int					key_press(int keycode, t_map_utils *cub);

/*    print_map.c   */
void				put_pixel_image(t_map_utils *window, int pixel_index,
						int color);
void				draw_background(t_map_utils *window, t_game *game);

#endif
