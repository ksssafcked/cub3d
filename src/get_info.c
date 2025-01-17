/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:06:21 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/17 14:06:51 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_angle(char c)
{
	if (c == 'N')
		return (-M_PI_2);
	else if (c == 'S')
		return (M_PI_2);
	else if (c == 'E')
		return (M_PI);
	else
		return (0);
}

void	get_player_pos(t_game *game)
{
	t_map *current = game->map;
	int	i;
	int	j;

	j = 0;
	while (current)
	{
		i = 0;
		while (current->coor[i])
		{
			if (current->coor[i] == 'N' || current->coor[i] == 'W' || current->coor[i] == 'S' || current->coor[i] == 'E')
			{
				game->player->x = i + 0.5;
				game->player->y = j + 0.5;
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->player->angle = get_angle(current->coor[i]);
				game->dirX = cos(game->player->angle);
				game->dirY = sin(game->player->angle);
				game->planeX = -sin(game->player->angle) * 0.66;
				game->planeY = cos(game->player->angle) * 0.66;
			}
			i++;
		}
		current = current->next;
		j++;
	}
}

char	**get_full_map(t_game *game)
{
	char	**map;
	t_map *current = game->map;
	int i;

	map = malloc(sizeof(char *) * (game->height_max + 1));
	if (!map)
		return (NULL);
	i = 0;
	get_player_pos(game);
	while (current)
	{
		map[i] = malloc(sizeof(char) * (game->length_max + 1));
		map[i] = strcpy_no_nl(game, current->coor, map[i], game->length_max);
		i++;
		current = current->next;
	}
	map[i] = NULL;
	return (map);
}
