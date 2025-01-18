/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:13:56 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:07:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall(t_map_utils *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || (size_t)map_x >= cub->game->length_max || map_y < 0
		|| (size_t)map_y >= cub->game->height_max)
		return (1);
	if (cub->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	change_pos(t_map_utils *cub, double *x, double *y)
{
	if (cub->key_w)
	{
		*x += cos(cub->game->player->angle) * cub->game->player->move_speed;
		*y += sin(cub->game->player->angle) * cub->game->player->move_speed;
	}
	if (cub->key_s)
	{
		*x -= cos(cub->game->player->angle) * cub->game->player->move_speed;
		*y -= sin(cub->game->player->angle) * cub->game->player->move_speed;
	}
	if (cub->key_a)
	{
		*x += sin(cub->game->player->angle) * cub->game->player->move_speed;
		*y -= cos(cub->game->player->angle) * cub->game->player->move_speed;
	}
	if (cub->key_d)
	{
		*x -= sin(cub->game->player->angle) * cub->game->player->move_speed;
		*y += cos(cub->game->player->angle) * cub->game->player->move_speed;
	}
}

int	change_dir(t_map_utils *cub)
{
	double	angle;
	double	new_x;
	double	new_y;

	angle = cub->game->player->angle;
	new_x = cub->game->player->x;
	new_y = cub->game->player->y;
	if (cub->key_w || cub->key_s || cub->key_a || cub->key_d)
		change_pos(cub, &new_x, &new_y);
	if (!is_wall(cub, new_x, new_y))
	{
		cub->game->player->x = new_x;
		cub->game->player->y = new_y;
	}
	if (cub->key_left)
		angle -= cub->game->player->move_speed;
	if (cub->key_right)
		angle += cub->game->player->move_speed;
	cub->game->player->angle = angle;
	draw_3d_view(cub);
	mlx_clear_window(cub->mlx, cub->window);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
	return (0);
}
