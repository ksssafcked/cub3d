/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:31:42 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/15 16:34:15 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


t_point	rotate_x(t_point p, double angle)
{
	int	temp;

	temp = p.y;
	p.y = (cos(angle) * temp) + (-sin(angle) * p.z);
	p.z = (sin(angle) * temp) + (cos(angle) * p.z);
	return (p);
}

t_point	rotate_y(t_point p, double angle)
{
	int	temp;

	temp = p.x;
	p.x = (cos(angle) * temp) + (sin(angle) * p.z);
	p.z = (-sin(angle) * temp) + (cos(angle) * p.z);
	return (p);
}

t_point	rotate_z(t_point p, double angle)
{
	int	temp;

	temp = p.x;
	p.x = (cos(angle) * temp) + (-sin(angle) * p.y);
	p.y = (sin(angle) * temp) + (cos(angle) * p.y);
	return (p);
}

t_point	iso(t_game *game, t_point p, int far)
{
	double	angle;

	angle = asin(1 / sqrt(3));
	p.x *= (far);
	p.y *= (far);
	p.z *= (far);
	p = rotate_x(p, angle);
	p = rotate_y(p, -0.785398);
	p.x += ((game->length_max * far) / 2);
	p.y += (HEIGHT / 2) - (game->height_max * far) / 2;
	return (p);
}


void	put_pixel_to_image(t_map_utils *fdf, t_point p)
{
	int	pixel_index;

	if (p.x >= 0 && p.y >= 0 && p.x < LENGTH && p.y < HEIGHT)
	{
		pixel_index = (p.y * fdf->size_line) + (p.x * (fdf->bpp / 8));
		fdf->img_data[pixel_index] = p.color & 0xFF;
		fdf->img_data[pixel_index + 1] = (p.color >> 8) & 0xFF;
		fdf->img_data[pixel_index + 2] = (p.color >> 16) & 0xFF;
	}
}

void	bresenheim(t_map_utils *fdf, t_point start, t_point end, t_vector v)
{
	while (1)
	{
		put_pixel_to_image(fdf, start);
		if (start.x == end.x && start.y == end.y)
			return ;
		v.e2 = v.err * 2;
		if (v.e2 > -v.dy)
		{
			v.err -= v.dy;
			start.x += v.sx;
		}
		if (v.e2 < v.dx)
		{
			v.err += v.dx;
			start.y += v.sy;
		}
	}
}

void	draw_line(t_map_utils *fdf, t_point start, t_point end)
{
	t_vector	v;

	v.dx = abs(end.x - start.x);
	v.dy = abs(end.y - start.y);
	if (start.x < end.x)
		v.sx = 1;
	else
		v.sx = -1;
	if (start.y < end.y)
		v.sy = 1;
	else
		v.sy = -1;
	v.err = v.dx - v.dy;
	bresenheim(fdf, start, end, v);
}

t_point	normalise(t_game *game, t_point p, int far)
{
	p.x *= (far);
	p.y *= (far);
	p.z *= (far);
	(void)game;
	p.x += LENGTH / 2 - (game->length_max * far) / 2;
	p.y += (HEIGHT / 2) - (game->height_max * far) / 2;
	return (p);
}

void	draw_background(t_map_utils *window, t_game *game)
{
	int	x;
	int	y;
	int	color_floor;
	int	color_ceil;
	int	pixel_index;

	color_floor = game->floor_color;
	color_ceil = game->ceiling_color;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < LENGTH)
		{
			pixel_index = (y * window->size_line) + (x * (window->bpp / 8));
			if (y < HEIGHT / 2)
			{
				window->img_data[pixel_index + 0] = color_ceil & 0xFF;
				window->img_data[pixel_index + 1] = (color_ceil >> 8) & 0xFF;
				window->img_data[pixel_index + 2] = (color_ceil >> 16) & 0xFF;
			}
			else
			{
				window->img_data[pixel_index + 0] = color_floor & 0xFF;
				window->img_data[pixel_index + 1] = (color_floor >> 8) & 0xFF;
				window->img_data[pixel_index + 2] = (color_floor >> 16) & 0xFF;
			}
			x++;
		}
		y++;
	}
}

t_point	get_player_point(t_game *game, double x, double y, int far)
{
	t_point p;

	x *= (far);
	y *= (far);
	x += LENGTH / 2 - (game->length_max * far) / 2;
	y += (HEIGHT / 2) - (game->height_max * far) / 2;
	p.x = (int)x;
	p.y = (int)y;
	return (p);
}

void	draw_player(t_map_utils *window, t_game *game)
{
	t_point a;
	t_point b;

	a = get_player_point(game, game->player->x, game->player->y, 15);
	a.color = 0xFF00FFFF;
	b = get_player_point(game, game->player->x + game->dirX, game->player->y + game->dirY, 15);
	b.color = 0xFF00FFFF;
	draw_line(window, a, b);
}

void	draw_map(t_map_utils *window, t_game *game)
{
	char	**map;
	int	i;
	int	j;
	t_point a;
	t_point	b;

	i = 0;
	(void)game;
	map = window->map;
	draw_background(window, game);
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == '1' && map[i][j + 1] && map[i][j + 1] == '1')
			{
				a.x = j;
				a.y = i;
				b.x = j + 1;
				b.y = i;
				a.color = 0xFFFF00FF;
				b.color = 0xFFFF00FF;
				a = normalise(game, a, 15);
				b = normalise(game, b, 15);
				draw_line(window, a, b);
			}
			if (map[i + 1] && map[i][j] == '1' && map[i + 1][j] == '1')
			{
				a.x = j;
				a.y = i;
				b.x = j;
				b.y = i + 1;
				a.color = 0xFFFF00FF;
				b.color = 0xFFFF00FF;
				a = normalise(game, a, 15);
				b = normalise(game, b, 15);
				draw_line(window, a, b);
			}
			j++;
		}
		i++;
	}
	draw_player(window, game);
}
