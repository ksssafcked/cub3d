/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:49:26 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/11 16:07:39 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>
# define LENGTH 1024
# define HEIGHT 720

/*		structs		*/

typedef struct s_game
{
	struct s_map	*map;
	struct s_player	*player;
	size_t			length_max;
	size_t			height_max;
	unsigned int	color;
	unsigned int	top_color;
}					t_game;

typedef struct s_map
{
	char			*coor;
	int				length;
	struct s_map	*next;
}					t_map;

typedef struct s_player
{
	int				x;
	int				y;
	char			direction;
}					t_player;

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
}			t_map_utils;

/*		parser.c	*/

t_game				*game_parser(char *file);
void				*free_map(t_map *map);
void				draw_map(t_map_utils *window, t_game *game);

#endif