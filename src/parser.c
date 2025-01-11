/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:06:07 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/10 17:51:24 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(t_map *map)
{
	t_map	*current;

	current = map;
	while (current)
	{
		printf("%s", current->coor);
		current = current->next;
	}
}

void	*free_map(t_map *map)
{
    t_map	*current;
    t_map	*next;

    current = map;
    while (current)
    {
        next = current->next;
        free(current->coor);
		free(current);
        current = next;
    }
    return (NULL);
}

void	parse_map(t_game *game, int fd)
{
	t_map	*map;
	int		i;

	map = malloc(sizeof(t_map));
	game->map = map;
	if (!map)
		return ;
	map->coor = get_next_line(fd);
	if (!map->coor)
		return ;
	game->length_max = ft_strlen(map->coor) - 1;
	while (map->coor)
	{
		map->next = malloc(sizeof(t_map));
		if (!map->next)
		{
			game->map = free_map(game->map);
			return ;
		}
		map->next->coor = get_next_line(fd);
		if (!map->next->coor)
		{
			free(map->next);
			break;
		}
		map = map->next;
		if (game->length_max <  (ft_strlen(map->coor) - 1))
			game->length_max = ft_strlen(map->coor) - 1;
	}
	map->next = NULL;
	map = game->map;
	i = 0;
	while (map)
	{
		i++;
		map = map->next;
	}
	game->height_max = i;
	return ;
}

t_game	*game_parser(char *file)
{
	int	fd;
	t_game	*game;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	game = malloc(sizeof(t_game));
	if (!game)
		return (perror("malloc"), NULL);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (free(game), perror("malloc"), NULL);
	parse_map(game, fd);
	close(fd);
	if (!game->map)
		return (free(game), NULL);
	// print_map(game->map);
	return (game);
}
