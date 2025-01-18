/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:06:07 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:10:50 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static int	skip_spaces_and_tabs(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int	check_map_closed(t_game *game)
{
	t_map	*current;
	int		i;
	int		len;
	int		row_index;

	current = game->map;
	row_index = 0;
	if (!current || !current->coor)
		return (0);
	i = skip_spaces_and_tabs(current->coor);
	while (current->coor[i] && current->coor[i] != '\n')
	{
		if (current->coor[i] != '1' && current->coor[i] != '\0')
			return (printf("First row not closed at position %d: '%c'\n", i,
					current->coor[i]), 0);
		i++;
	}
	while (current->next)
	{
		current = current->next;
		row_index++;
	}
	i = skip_spaces_and_tabs(current->coor);
	while (current->coor[i] && current->coor[i] != '\n')
	{
		if (current->coor[i] != '1' && current->coor[i] != '\0')
			return (printf("Last row not closed at position %d: '%c'\n", i,
					current->coor[i]), 0);
		i++;
	}
	current = game->map;
	row_index = 0;
	while (current)
	{
		len = ft_strlen(current->coor);
		if (len > 0 && current->coor[len - 1] == '\n')
			len--;
		if (len < 1)
			return (printf("Empty row at index %d\n", row_index), 0);
		i = skip_spaces_and_tabs(current->coor);
		if (current->coor[i] != '1')
			return (printf("Row %d not closed on left side: starts with '%c'\n",
					row_index, current->coor[i]), 0);
		i = len - 1;
		while (i >= 0 && (current->coor[i] == ' ' || current->coor[i] == '\t'))
			i--;
		if (i >= 0 && current->coor[i] != '1')
			return (printf("Row %d not closed on right side: ends with '%c'\n",
					row_index, current->coor[i]), 0);
		current = current->next;
		row_index++;
	}
	return (1);
}

void	parse_map_until_end(t_game *game, int fd, t_map *map)
{
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
			break ;
		}
		map = map->next;
		if (game->length_max < (ft_strlen(map->coor) - 1))
			game->length_max = ft_strlen(map->coor) - 1;
	}
	map->next = NULL;
}

void	parse_map_with_first_line(t_game *game, int fd, char *first_line)
{
	t_map	*map;
	int		i;

	map = malloc(sizeof(t_map));
	game->map = map;
	if (!map)
		return ;
	map->coor = first_line;
	if (!map->coor)
		return ;
	game->length_max = ft_strlen(map->coor) - 1;
	parse_map_until_end(game, fd, map);
	if (!game->map)
		return ;
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

int	is_direction_or_color(char *line)
{
	if (!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2))
		return (1);
	if (!ft_strncmp("WE", line, 2) || !ft_strncmp("EA", line, 2))
		return (1);
	if (!ft_strncmp("F", line, 1) || !ft_strncmp("C", line, 1))
		return (1);
	return (0);
}

char	*skip_config_lines(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_direction_or_color(line))
		{
			if (!parse_config_line(line, game))
			{
				fprintf(stderr, "Error parsing config line: %s\n", line);
				return (free(line), NULL);
			}
			free(line);
		}
		else if (line[0] == '\n' || line[0] == ' ')
			free(line);
		else
			break ;
		line = get_next_line(fd);
	}
	return (line);
}

int	check_textures_defined(t_game *game)
{
	if (!game->no_defined || !game->so_defined || !game->we_defined || !game->ea_defined || !game->f_defined || !game->c_defined)
		return (0);
	return (1);
}

t_game	*game_parser(char *file)
{
	int		fd;
	t_game	*game;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	game = malloc(sizeof(t_game));
	if (!game)
		return (perror("malloc"), NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (free(game), perror("malloc"), NULL);
	line = skip_config_lines(fd, game);
	if (!line)
		return (free(game->player), free(game), NULL);
	parse_map_with_first_line(game, fd, line);
	close(fd);
	if (!game->map)
		return (free(game->player), free(game), NULL);
	if (!check_map_closed(game))
	{
		fprintf(stderr, "Error\nMap is not closed/surrounded by walls.\n");
		return (free_map(game->map), free(game->player), free(game), NULL);
	}
	if (!check_textures_defined(game))
		return (free_map(game->map), free(game->player), free(game), NULL);
	return (game);
}
