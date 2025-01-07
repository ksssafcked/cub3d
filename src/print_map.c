/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:31:42 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/07 19:24:45 by lsaiti           ###   ########.fr       */
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
				mlx_pixel_put(window->mlx, window->window, (int)(i * (LENGTH / map->length)) + ((LENGTH / map->length) / 2), j * (40), 0xFFFFFF);
			i++;
		}
		map = map->next;
		j++;
	}
}
