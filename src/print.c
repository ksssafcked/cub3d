/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:44:53 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/17 13:49:16 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel_image(t_map_utils *window, int pixel_index, int color)
{
	window->img_data[pixel_index + 0] = color & 0xFF;
	window->img_data[pixel_index + 1] = (color >> 8) & 0xFF;
	window->img_data[pixel_index + 2] = (color >> 16) & 0xFF;
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
				put_pixel_image(window, pixel_index, color_ceil);
			else
				put_pixel_image(window, pixel_index, color_floor);
			x++;
		}
		y++;
	}
}
