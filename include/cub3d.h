/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:49:26 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/16 17:43:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl.h"
# include "mlx.h"
# include <stddef.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>
# define LENGTH 800
# define HEIGHT 600

/*		structs		*/

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

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
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	int				no_defined;
    int				so_defined;
    int				we_defined;
    int				ea_defined;
    int				f_defined;
    int				c_defined;
}					t_game;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		error;
}			t_point;

typedef struct s_vector
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}			t_vector;

typedef struct t_map_utils
{
	char	**map;
	t_point	**point;
	t_point	*start;
	int		height;
	int		width;
	void	*mlx;
	void	*window;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		far;
	struct s_game	*game;
	int key_w;
    int key_s;
    int key_a;
    int key_d;
	int key_left;
    int key_right;
}			t_map_utils;

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


/*	   ft_split.c   */

char				**ft_split(char const *str, char c);
void				free_split(char **split);

/*    print_map.c   */

void				draw_background(t_map_utils *window, t_game *game);

void				draw_3d_view(t_map_utils *fdf);

#endif
