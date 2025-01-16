/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qudomino <qudomino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:13:17 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/14 12:54:54 by qudomino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int parse_texture(char *line, t_game *game)
{
    char **split = ft_split(line, ' ');
    if (!split || !split[0] || !split[1])
    {
        if (split) free_split(split);
        return 0;
    }
    if (!ft_strcmp(split[0], "NO"))
    {
        if (game->no_defined == 1)
            return (free_split(split), 0);
        game->no_defined = 1;
        game->path_no = ft_strdup(split[1]);
    }
    else if (!ft_strcmp(split[0], "SO"))
    {
        if (game->so_defined == 1)
            return (free_split(split), 0);
        game->so_defined = 1;
        game->path_so = ft_strdup(split[1]);
    }
    else if (!ft_strcmp(split[0], "WE"))
    {
        if (game->we_defined == 1)
            return (free_split(split), 0);
        game->we_defined = 1;
        game->path_we = ft_strdup(split[1]);
    }
    else if (!ft_strcmp(split[0], "EA"))
    {
        if (game->ea_defined == 1)
            return (free_split(split), 0);
        game->ea_defined = 1;
        game->path_ea = ft_strdup(split[1]);
    }
    else
    {
        free_split(split);
        return 0;
    }
    free_split(split);
    return 1;
}

static int parse_color(char *line, t_game *game)
{
    char **split_space = ft_split(line, ' ');
    if (!split_space || !split_space[0] || !split_space[1])
    {
        if (split_space) free_split(split_space);
        return 0;
    }
    if ((!ft_strcmp(split_space[0], "F") && game->f_defined == 1) ||
        (!ft_strcmp(split_space[0], "C") && game->c_defined == 1))
    {
        free_split(split_space);
        return 0;
    }
    char **split_comma = ft_split(split_space[1], ',');
    free_split(split_space);
    if (!split_comma || !split_comma[0] || !split_comma[1] || !split_comma[2])
    {
        if (split_comma) free_split(split_comma);
        return 0;
    }
    int r = ft_atoi(split_comma[0]);
    int g = ft_atoi(split_comma[1]);
    int b = ft_atoi(split_comma[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_split(split_comma);
        return 0;
    }
    unsigned int color = (r << 16) | (g << 8) | b;
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
    {
        free_split(split_comma);
        return 0;
    }
    free_split(split_comma);
    return 1;
}

int parse_config_line(char *line, t_game *game)
{
    if (!line || !*line || line[0] == '\n')
        return (1);
    if (parse_texture(line, game))
        return (1);
    if (parse_color(line, game))
        return (1);
    return (0);
}
