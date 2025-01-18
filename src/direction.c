/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:13:56 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 18:54:52 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall(t_map_utils *fdf, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || (size_t)map_x >= fdf->game->length_max || map_y < 0
		|| (size_t)map_y >= fdf->game->height_max)
		return (1);
	if (fdf->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	change_pos(t_map_utils *fdf, double *x, double *y)
{
	if (fdf->key_w)
	{
		*x += cos(fdf->game->player->angle) * fdf->game->player->move_speed;
		*y += sin(fdf->game->player->angle) * fdf->game->player->move_speed;
	}
	if (fdf->key_s)
	{
		*x -= cos(fdf->game->player->angle) * fdf->game->player->move_speed;
		*y -= sin(fdf->game->player->angle) * fdf->game->player->move_speed;
	}
	if (fdf->key_a)
	{
		*x += sin(fdf->game->player->angle) * fdf->game->player->move_speed;
		*y -= cos(fdf->game->player->angle) * fdf->game->player->move_speed;
	}
	if (fdf->key_d)
	{
		*x -= sin(fdf->game->player->angle) * fdf->game->player->move_speed;
		*y += cos(fdf->game->player->angle) * fdf->game->player->move_speed;
	}
}

int	change_dir(t_map_utils *fdf)
{
	double	angle;
	double	new_x;
	double	new_y;

	angle = fdf->game->player->angle;
	new_x = fdf->game->player->x;
	new_y = fdf->game->player->y;
	if (fdf->key_w || fdf->key_s || fdf->key_a || fdf->key_d)
		change_pos(fdf, &new_x, &new_y);
	if (!is_wall(fdf, new_x, new_y))
	{
		fdf->game->player->x = new_x;
		fdf->game->player->y = new_y;
	}
	if (fdf->key_left)
		angle -= fdf->game->player->move_speed;
	if (fdf->key_right)
		angle += fdf->game->player->move_speed;
	fdf->game->player->angle = angle;
	draw_3d_view(fdf);
	mlx_clear_window(fdf->mlx, fdf->window);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	return (0);
}
