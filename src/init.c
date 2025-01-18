/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:40:44 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:16:12 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map_utils	*map_init(void)
{
	t_map_utils	*cub;

	cub = malloc(sizeof(t_map_utils));
	if (!cub)
		return (NULL);
	cub->key_w = 0;
	cub->key_s = 0;
	cub->key_d = 0;
	cub->key_a = 0;
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (NULL);
	cub->window = mlx_new_window(cub->mlx, LENGTH, HEIGHT, "Cub3d");
	if (!cub->window)
		free_all(cub);
	return (cub);
}

void	init_image(t_map_utils *cub)
{
	cub->img = mlx_new_image(cub->mlx, LENGTH, HEIGHT);
	cub->img_data = mlx_get_data_addr(cub->img, &cub->bpp, &cub->size_line,
			&cub->endian);
}

t_map_utils	*init_textures(t_map_utils *cub)
{
	cub->game->tex_no.img = mlx_xpm_file_to_image(cub->mlx, cub->game->path_no,
			&cub->game->tex_no.width, &cub->game->tex_no.height);
	cub->game->tex_so.img = mlx_xpm_file_to_image(cub->mlx, cub->game->path_so,
			&cub->game->tex_so.width, &cub->game->tex_so.height);
	cub->game->tex_we.img = mlx_xpm_file_to_image(cub->mlx, cub->game->path_we,
			&cub->game->tex_we.width, &cub->game->tex_we.height);
	cub->game->tex_ea.img = mlx_xpm_file_to_image(cub->mlx, cub->game->path_ea,
			&cub->game->tex_ea.width, &cub->game->tex_ea.height);
	if (!cub->game->tex_no.img || !cub->game->tex_so.img
		|| !cub->game->tex_we.img || !cub->game->tex_ea.img)
		return (write(2, "Failed to load texture\n", 23), close_all(cub), NULL);
	cub->game->tex_ea.addr = (int *)mlx_get_data_addr(cub->game->tex_ea.img,
			&cub->game->tex_ea.bpp, &cub->game->tex_ea.size_line,
			&cub->game->tex_ea.endian);
	cub->game->tex_we.addr = (int *)mlx_get_data_addr(cub->game->tex_we.img,
			&cub->game->tex_we.bpp, &cub->game->tex_we.size_line,
			&cub->game->tex_we.endian);
	cub->game->tex_so.addr = (int *)mlx_get_data_addr(cub->game->tex_so.img,
			&cub->game->tex_so.bpp, &cub->game->tex_so.size_line,
			&cub->game->tex_so.endian);
	cub->game->tex_no.addr = (int *)mlx_get_data_addr(cub->game->tex_no.img,
			&cub->game->tex_no.bpp, &cub->game->tex_no.size_line,
			&cub->game->tex_no.endian);
	return (cub);
}

t_map_utils	*init_cub(t_game *game)
{
	t_map_utils	*cub;

	cub = map_init();
	if (!cub)
		return (write(2, "FAILED TO INIT MAP!\n", 20), NULL);
	cub->map = get_full_map(game);
	if (!cub->map)
		return (close_all(cub), write(2, "Error: Failed to load map.\n", 26),
			NULL);
	cub->game = game;
	init_image(cub);
	if (!cub->img)
		return (close_all(cub), write(2, "Error: Failed to create image.\n",
				31), NULL);
	cub = init_textures(cub);
	return (cub);
}
