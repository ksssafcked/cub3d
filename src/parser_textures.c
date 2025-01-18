/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:51:15 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 15:51:41 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_north_south(char **split, t_game *game)
{
	if (!ft_strcmp(split[0], "NO"))
	{
		if (game->no_defined == 1)
		{
			free_split(split);
			return (0);
		}
		game->no_defined = 1;
		game->path_no = ft_strdup(split[1]);
		trim_end(&game->path_no);
	}
	else if (!ft_strcmp(split[0], "SO"))
	{
		if (game->so_defined == 1)
		{
			free_split(split);
			return (0);
		}
		game->so_defined = 1;
		game->path_so = ft_strdup(split[1]);
		trim_end(&game->path_so);
	}
	return (1);
}

int	parse_east_west(char **split, t_game *game)
{
	if (!ft_strcmp(split[0], "WE"))
	{
		if (game->we_defined == 1)
		{
			free_split(split);
			return (0);
		}
		game->we_defined = 1;
		game->path_we = ft_strdup(split[1]);
		trim_end(&game->path_we);
	}
	else if (!ft_strcmp(split[0], "EA"))
	{
		if (game->ea_defined == 1)
		{
			free_split(split);
			return (0);
		}
		game->ea_defined = 1;
		game->path_ea = ft_strdup(split[1]);
		trim_end(&game->path_ea);
	}
	return (1);
}

int	parse_texture(char *line, t_game *game)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		if (split)
			free_split(split);
		return (0);
	}
	if (!ft_strcmp(split[0], "NO") || !ft_strcmp(split[0], "SO"))
	{
		if (!parse_north_south(split, game))
			return (0);
	}
	else if (!ft_strcmp(split[0], "WE") || !ft_strcmp(split[0], "EA"))
	{
		if (!parse_east_west(split, game))
			return (0);
	}
	else
		return (free_split(split), 0);
	free_split(split);
	return (1);
}
