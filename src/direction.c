/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:13:56 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/17 14:15:10 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_wall(t_map_utils *fdf, double x, double y)
{
	int mapX = (int)x;
	int mapY = (int)y;

	// Vérifiez les limites de la carte
	if (mapX < 0 || (size_t)mapX >= fdf->game->length_max || mapY < 0 || (size_t)mapY >= fdf->game->height_max)
		return (1); // Hors de la carte = mur

	// Vérifiez si la case est un mur
	if (fdf->map[mapY][mapX] == '1')
		return (1); // Mur

	return (0); // Pas de mur
}

int change_dir(t_map_utils *fdf)
{
	double angle = fdf->game->player->angle;
	double move_speed = 0.015;
	double rot_speed = M_PI_4 / 20;
	double new_x = fdf->game->player->x;
	double new_y = fdf->game->player->y;

	if (fdf->key_w) {
		new_x += cos(angle) * move_speed;
		new_y += sin(angle) * move_speed;
	}
	if (fdf->key_s) {
		new_x -= cos(angle) * move_speed;
		new_y -= sin(angle) * move_speed;
	}
	if (fdf->key_a) {
		new_x += sin(angle) * move_speed;
		new_y -= cos(angle) * move_speed;
	}
	if (fdf->key_d) {
		new_x -= sin(angle) * move_speed;
		new_y += cos(angle) * move_speed;
	}
	if (!is_wall(fdf, new_x, new_y))
	{
		fdf->game->player->x = new_x;
		fdf->game->player->y = new_y;
	}
	else
		printf("Collision detected at (%f, %f)\n", new_x, new_y);
	if (fdf->key_left)
		angle -= rot_speed;
	if (fdf->key_right)
		angle += rot_speed;
	fdf->game->player->angle = angle;
	fdf->game->dirX = cos(angle);
	fdf->game->dirY = sin(angle);
	draw_3d_view(fdf);
	mlx_clear_window(fdf->mlx, fdf->window);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	return (0);
}
