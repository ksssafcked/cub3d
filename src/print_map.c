/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:31:42 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/09 17:19:27 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map(t_map_utils *window, t_game *game)
{
	t_map	*map;
	// int		height;
	int		i;
	int		j;

	map = (t_map*)(game->map);
	j = 0;
	while (map)
	{
		i = 0;
		while (map->coor[i])
		{
			if (map->coor[i] == '1')
				mlx_pixel_put(window->mlx, window->window, (int)(i * (LENGTH / game->length_max)) + ((LENGTH / game->length_max) / 2), j * ((HEIGHT / game->height_max)) + ((HEIGHT / game->height_max) / 2), 0xFFFFFF);
			else if (map->coor[i] == 'N' || map->coor[i] == 'W' || map->coor[i] == 'S' || map->coor[i] == 'E')
			{
				game->player->x = i;
				game->player->y = j;
				game->player->direction = map->coor[i];
				mlx_pixel_put(window->mlx, window->window, (int)(i * (LENGTH / game->length_max)) + ((LENGTH / game->length_max) / 2), j * ((HEIGHT / game->height_max)) + ((HEIGHT / game->height_max) / 2), 0xFF00FF);
			}
			i++;
		}
		map = map->next;
		j++;
	}
}
