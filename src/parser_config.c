/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:13:17 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/18 17:59:48 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	trim_end(char **str)
{
	size_t	len;

	len = ft_strlen(*str);
	while (len > 0 && ((*str)[len - 1] == '\n' || (*str)[len - 1] == ' '))
	{
		(*str)[len - 1] = '\0';
		len--;
	}
}

int	change_color(char **split_comma, char *line, t_game *game)
{
	int				r;
	int				g;
	int				b;
	unsigned int	color;

	r = ft_atoi(split_comma[0]);
	g = ft_atoi(split_comma[1]);
	b = ft_atoi(split_comma[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(split_comma), 0);
	color = (r << 16) | (g << 8) | b;
	if (!ft_strncmp(line, "F ", 2))
	{
		game->floor_color = color;
		game->f_defined = 1;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		game->ceiling_color = color;
		game->c_defined = 1;
	}
	else
		return (free_split(split_comma), 0);
	return (1);
}

int	parse_color(char *line, t_game *game)
{
	char	**split_space;
	char	**split_comma;

	split_space = ft_split(line, ' ');
	if (!split_space || !split_space[0] || !split_space[1])
	{
		if (split_space)
			free_split(split_space);
		return (0);
	}
	if ((!ft_strcmp(split_space[0], "F") && game->f_defined == 1)
		|| (!ft_strcmp(split_space[0], "C") && game->c_defined == 1))
		return (free_split(split_space), 0);
	split_comma = ft_split(split_space[1], ',');
	free_split(split_space);
	if (!split_comma || !split_comma[0] || !split_comma[1] || !split_comma[2])
	{
		if (split_comma)
			free_split(split_comma);
		return (0);
	}
	if (!change_color(split_comma, line, game))
		return (0);
	return (free_split(split_comma), 1);
}

int	parse_config_line(char *line, t_game *game)
{
	if (!line || !*line || line[0] == '\n')
		return (1);
	if (parse_texture(line, game))
		return (1);
	if (parse_color(line, game))
		return (1);
	return (0);
}
