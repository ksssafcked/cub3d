/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:49:26 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/09 17:24:35 by lsaiti           ###   ########.fr       */
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
# define LENGTH 800
# define HEIGHT 600

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

typedef struct t_map_utils
{
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
}					t_map_utils;

/*		parser.c	*/

t_game				*game_parser(char *file);
void				*free_map(t_map *map);
void				draw_map(t_map_utils *window, t_game *game);

#endif