/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:06:21 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 18:54:00 by lsaiti           ###   ########.fr       */
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
	t_map	*current;
	int		i;
	int		j;

	current = game->map;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->coor[i])
		{
			if (current->coor[i] == 'N' || current->coor[i] == 'W'
				|| current->coor[i] == 'S' || current->coor[i] == 'E')
			{
				game->player->x = i + 0.5;
				game->player->y = j + 0.5;
				game->player->angle = get_angle(current->coor[i]);
				game->player->move_speed = 0.015;
				game->player->rot_speed = M_PI_4 / 20;
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
	t_map	*current;
	int		i;

	current = game->map;
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

int	get_texture(t_map_utils *fdf, t_view *view)
{
	if (view->side == 0)
	{
		if (view->raydir_x > 0)
			view->tex = &fdf->game->tex_ea;
		else
			view->tex = &fdf->game->tex_we;
	}
	else
	{
		if (view->raydir_y > 0)
			view->tex = &fdf->game->tex_so;
		else
			view->tex = &fdf->game->tex_no;
	}
	if (!view->tex || !view->tex->img || !view->tex->addr)
	{
		fprintf(stderr, "Error: Texture not initialized.\n");
		return (0);
	}
	if (view->tex->width <= 0 || view->tex->height <= 0)
	{
		fprintf(stderr, "Error: Invalid texture dimensions.\n");
		return (0);
	}
	return (1);
}
