/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:11:41 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 12:52:20 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	printer_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

char	*strcpy_no_nl(t_game *game, char *source, char *dest, int size)
{
	int	i;

	i = 0;
	while (source[i] && source[i] != '\n' && i < size)
	{
		if (source[i] == '1')
			dest[i] = source[i];
		else
		{
			if (source[i] == 'N' || source[i] == 'W' || source[i] == 'S'
				|| source[i] == 'E')
				game->player->direction = source[i];
			dest[i] = '0';
		}
		i++;
	}
	while (i < size)
		dest[i++] = '\0';
	dest[i] = '\0';
	return (dest);
}
